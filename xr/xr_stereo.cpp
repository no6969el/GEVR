/*
 * xr_stereo.cpp — GoldenEyeVR Phase 2, step 1: a real stereo image in the headset.
 *
 * Renders a wireframe test world to both eyes through OpenXR + D3D12 and submits
 * an XrCompositionLayerProjection. It has nothing to do with GoldenRecomp.exe and
 * cannot affect it.
 *
 * WHY THIS EXISTS
 * ---------------
 * Two unknowns block Phase 1 step 3 (two render targets inside RT64), and they
 * are independent:
 *
 *   1. Does the XR plumbing work on this rig — swapchains, per-eye rendering,
 *      layer submission, pose tracking?
 *   2. Is the per-eye frustum maths in patches/ge_vr_bindtest.c actually correct
 *      in STEREO, as opposed to merely "not obviously wrong on a monitor"?
 *
 * Answering (2) inside RT64 means solving (1) first and debugging both at once.
 * This program answers both separately, which is the whole point.
 *
 * THE MATHS IS DELIBERATELY THE SAME AS THE PATCH
 * -----------------------------------------------
 * geVrBuildProj() in the patch computes, from the four eye tangents:
 *
 *     sx = 2 / (tanRight - tanLeft)          -> [0][0]
 *     sy = 2 / (tanUp    - tanDown)          -> [1][1]
 *     ox = (tanRight + tanLeft) / (tanRight - tanLeft)   -> [2][0]
 *     oy = (tanUp    + tanDown) / (tanUp    - tanDown)   -> [2][1]
 *
 * This file computes those four the same way, stores them at the same row-vector
 * positions, and the shader uses `row_major` + `mul(pos, M)` so the layout is
 * literally the one guPerspectiveF produces. If the world fuses here, that
 * formula and that placement are right.
 *
 * THE DEPTH ROW IS *NOT* THE SAME, AND MUST NOT BE "FIXED" TO MATCH
 * -----------------------------------------------------------------
 * The N64 clips to a symmetric depth range, so the patch uses the GL-style
 *     [2][2] = (n+f)/(n-f)      [3][2] = 2nf/(n-f)
 * D3D12 clips to [0,1], which needs
 *     [2][2] = f/(n-f)          [3][2] = nf/(n-f)
 * Both are correct for their own target. Someone will eventually notice the
 * mismatch and "correct" one of them; that person will break whichever they
 * touch. The x/y scale and skew terms — the parts step 1 actually changes — are
 * identical between the two conventions, which is exactly why this test is a
 * valid check of the patch.
 *
 * BUILD (VS developer shell, this directory):
 *   cl /std:c++17 /EHsc /O2 /nologo xr_stereo.cpp /I lib\openxr\include ^
 *      /link lib\openxr\native\x64\release\lib\openxr_loader.lib ^
 *            d3d12.lib dxgi.lib d3dcompiler.lib
 *
 * RUN: start SteamVR, put the headset on, run it. Esc in the console or removing
 * the headset ends the session. It prints per-eye numbers once at startup.
 */
#define XR_USE_GRAPHICS_API_D3D12
#define XR_USE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>
#include <shellapi.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>

#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>

#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <vector>

static XrInstance g_instance = XR_NULL_HANDLE;

static const char* xrStr(XrResult r) {
    static char buf[XR_MAX_RESULT_STRING_SIZE];
    if (g_instance != XR_NULL_HANDLE && XR_SUCCEEDED(xrResultToString(g_instance, r, buf))) return buf;
    snprintf(buf, sizeof(buf), "XrResult(%d)", (int) r);
    return buf;
}

#define CHK(expr)                                                      \
    do {                                                               \
        XrResult _r = (expr);                                          \
        if (XR_FAILED(_r)) {                                           \
            printf("\nFAILED: %s\n   -> %s\n", #expr, xrStr(_r));      \
            return 1;                                                  \
        }                                                              \
    } while (0)

#define HCHK(expr)                                                     \
    do {                                                               \
        HRESULT _h = (expr);                                           \
        if (FAILED(_h)) {                                              \
            printf("\nD3D FAILED: %s -> 0x%08lx\n", #expr, (unsigned long) _h); \
            return 1;                                                  \
        }                                                              \
    } while (0)

/* --- tiny row-vector matrix helpers --------------------------------------- *
 * Row-vector convention throughout: v' = v * M. This matches guPerspectiveF and
 * therefore matches the patch. It is NOT the convention most D3D samples use, so
 * the shader declares the matrix row_major and multiplies mul(pos, M). */
struct M4 {
    float m[4][4];
};

static M4 m4identity() {
    M4 r{};
    for (int i = 0; i < 4; i++) r.m[i][i] = 1.0f;
    return r;
}

static M4 m4mul(const M4& a, const M4& b) {
    M4 r{};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            float s = 0.0f;
            for (int k = 0; k < 4; k++) s += a.m[i][k] * b.m[k][j];
            r.m[i][j] = s;
        }
    return r;
}

/* Projection from the four tangents. The x/y scale and skew terms are computed
 * exactly as geVrBuildProj() does; only the depth row differs, per the header. */
static M4 m4projFromTangents(float tl, float tr, float tu, float td, float n, float f) {
    M4 p{};
    const float w = tr - tl;
    const float h = tu - td;

    p.m[0][0] = 2.0f / w;                 /* sx */
    p.m[1][1] = 2.0f / h;                 /* sy */
    p.m[2][0] = (tr + tl) / w;            /* ox — ROW 2, not column 2 */
    p.m[2][1] = (tu + td) / h;            /* oy */
    p.m[2][2] = f / (n - f);              /* D3D [0,1] depth, see header */
    p.m[2][3] = -1.0f;
    p.m[3][2] = (n * f) / (n - f);
    return p;
}

/* View matrix from an XrPosef. OpenXR is right-handed, -Z forward, Y up.
 * A world point becomes (w - position) * R^T, so in row-vector terms
 * V = translate(-position) * transpose(rotation). */
static M4 m4viewFromPose(const XrPosef& pose) {
    const XrQuaternionf& q = pose.orientation;
    const float x = q.x, y = q.y, z = q.z, w = q.w;

    /* R maps camera-local -> world, in row-vector layout. */
    M4 R = m4identity();
    R.m[0][0] = 1 - 2 * (y * y + z * z);
    R.m[0][1] = 2 * (x * y + z * w);
    R.m[0][2] = 2 * (x * z - y * w);
    R.m[1][0] = 2 * (x * y - z * w);
    R.m[1][1] = 1 - 2 * (x * x + z * z);
    R.m[1][2] = 2 * (y * z + x * w);
    R.m[2][0] = 2 * (x * z + y * w);
    R.m[2][1] = 2 * (y * z - x * w);
    R.m[2][2] = 1 - 2 * (x * x + y * y);

    M4 Rt = m4identity(); /* transpose = inverse, R is orthonormal */
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) Rt.m[i][j] = R.m[j][i];

    M4 T = m4identity();
    T.m[3][0] = -pose.position.x;
    T.m[3][1] = -pose.position.y;
    T.m[3][2] = -pose.position.z;

    return m4mul(T, Rt);
}

/* --- the test world -------------------------------------------------------- *
 * Wireframe only: one pipeline, one vertex buffer, line list. Everything here is
 * chosen to make a stereo error obvious to a human wearing the headset.
 *
 *   floor grid       a metric ruler. If the eyes disagree, grid lines double at
 *                    distance long before anything else looks wrong.
 *   centre pole      a vertical line dead ahead at 2 m. The single most sensitive
 *                    fusion target there is — vertical lines expose horizontal
 *                    disparity errors immediately.
 *   depth cubes      1, 2, 4, 8 m out. They should sit at plainly different
 *                    distances. If they all feel like they are on one plane, the
 *                    IPD offset is not reaching the view matrix.
 *   coloured axes    X red, Y green, Z blue from the origin, so "which way am I
 *                    facing" is never ambiguous while debugging. */
struct Vtx {
    float x, y, z;
    float r, g, b;
};

static void addLine(std::vector<Vtx>& v, float x0, float y0, float z0, float x1, float y1, float z1,
                    float r, float g, float b) {
    v.push_back({x0, y0, z0, r, g, b});
    v.push_back({x1, y1, z1, r, g, b});
}

static void addBox(std::vector<Vtx>& v, float cx, float cy, float cz, float s, float r, float g, float b) {
    const float h = s * 0.5f;
    const float xs[2] = {cx - h, cx + h};
    const float ys[2] = {cy - h, cy + h};
    const float zs[2] = {cz - h, cz + h};
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) {
            addLine(v, xs[0], ys[i], zs[j], xs[1], ys[i], zs[j], r, g, b);
            addLine(v, xs[i], ys[0], zs[j], xs[i], ys[1], zs[j], r, g, b);
            addLine(v, xs[i], ys[j], zs[0], xs[i], ys[j], zs[1], r, g, b);
        }
}

static std::vector<Vtx> buildWorld() {
    std::vector<Vtx> v;

    /* Grid now reaches -10 m so the farthest cube has floor under it. v1 stopped
     * at 5 m and left the 8 m cube floating in void with no depth reference. */
    for (int i = -12; i <= 12; i++) {
        const float t = i * 0.5f;
        const bool major = (i % 2) == 0;
        const float c = major ? 0.55f : 0.22f;
        addLine(v, t, 0.0f, -10.0f, t, 0.0f, 4.0f, c, c, c);
    }
    for (int i = -20; i <= 8; i++) {
        const float t = i * 0.5f;
        const bool major = (i % 2) == 0;
        const float c = major ? 0.55f : 0.22f;
        addLine(v, -6.0f, 0.0f, t, 6.0f, 0.0f, t, c, c, c);
    }

    /* FUSION POLE — moved to x = -1.5 so it stands ALONE. In v1 it was at
     * x=0, z=-2, which is exactly where the green cube sits, so the pole speared
     * straight through it and was useless as an isolated vertical. A vertical
     * line is the most sensitive horizontal-disparity target in the scene and it
     * only works if nothing else is near it. */
    addLine(v, -1.5f, 0.0f, -2.0f, -1.5f, 2.0f, -2.0f, 1.0f, 1.0f, 1.0f);
    for (int i = 1; i <= 4; i++) {
        const float y = i * 0.5f;
        addLine(v, -1.55f, y, -2.0f, -1.45f, y, -2.0f, 1.0f, 1.0f, 0.2f);
    }

    /* A second pole further out. Two isolated verticals at different depths let
     * you check that disparity SCALES with distance, not just that it exists. */
    addLine(v, 1.5f, 0.0f, -6.0f, 1.5f, 2.0f, -6.0f, 0.8f, 0.8f, 1.0f);

    /* ORIGIN MARKER — a small square on the floor at 0,0,0 with a vertical stub.
     * Stand on this and the cube sizes read as intended (near largest). Without
     * it there is no way to know where the origin is, and STAGE space puts it at
     * the centre of the play area, which is not where you happen to be standing. */
    addLine(v, -0.15f, 0.02f, -0.15f, 0.15f, 0.02f, -0.15f, 1.0f, 0.5f, 0.0f);
    addLine(v, 0.15f, 0.02f, -0.15f, 0.15f, 0.02f, 0.15f, 1.0f, 0.5f, 0.0f);
    addLine(v, 0.15f, 0.02f, 0.15f, -0.15f, 0.02f, 0.15f, 1.0f, 0.5f, 0.0f);
    addLine(v, -0.15f, 0.02f, 0.15f, -0.15f, 0.02f, -0.15f, 1.0f, 0.5f, 0.0f);
    addLine(v, 0.0f, 0.02f, 0.0f, 0.0f, 0.35f, 0.0f, 1.0f, 0.5f, 0.0f);

    addBox(v, 0.0f, 1.0f, -1.0f, 0.20f, 1.0f, 0.35f, 0.35f);
    addBox(v, 0.0f, 1.0f, -2.0f, 0.30f, 0.35f, 1.0f, 0.35f);
    addBox(v, 0.0f, 1.0f, -4.0f, 0.50f, 0.35f, 0.6f, 1.0f);
    addBox(v, 0.0f, 1.0f, -8.0f, 0.90f, 1.0f, 1.0f, 0.35f);

    addLine(v, 0, 0.01f, 0, 1, 0.01f, 0, 1, 0, 0);
    addLine(v, 0, 0.01f, 0, 0, 1.01f, 0, 0, 1, 0);
    addLine(v, 0, 0.01f, 0, 0, 0.01f, -1, 0, 0, 1);

    return v;
}

static const char* kShader = R"(
cbuffer Cb : register(b0) { row_major float4x4 gMvp; };
struct VSIn  { float3 pos : POSITION; float3 col : COLOR; };
struct VSOut { float4 pos : SV_POSITION; float3 col : COLOR; };
VSOut VSMain(VSIn i) {
    VSOut o;
    o.pos = mul(float4(i.pos, 1.0), gMvp);   /* row-vector, matches guPerspectiveF */
    o.col = i.col;
    return o;
}
float4 PSMain(VSOut i) : SV_TARGET { return float4(i.col, 1.0); }
)";

struct EyeTarget {
    XrSwapchain swapchain = XR_NULL_HANDLE;
    uint32_t w = 0, h = 0;
    std::vector<XrSwapchainImageD3D12KHR> images;
    ID3D12DescriptorHeap* rtvHeap = nullptr;
    ID3D12Resource* depth = nullptr;
    ID3D12DescriptorHeap* dsvHeap = nullptr;
};

int main() {
    /* Unbuffered: this gets run with stdout redirected to a file and inspected
     * while it is still running. Buffered output means the file stays empty for
     * the entire session, which makes remote diagnosis impossible. */
    setvbuf(stdout, nullptr, _IONBF, 0);
    printf("=== GoldenEyeVR stereo test ===\n\n");

    /* ---------------- OpenXR instance / system ---------------- */
    uint32_t extCount = 0;
    CHK(xrEnumerateInstanceExtensionProperties(nullptr, 0, &extCount, nullptr));
    std::vector<XrExtensionProperties> exts(extCount, {XR_TYPE_EXTENSION_PROPERTIES});
    CHK(xrEnumerateInstanceExtensionProperties(nullptr, extCount, &extCount, exts.data()));
    bool haveD3D12 = false;
    for (const auto& e : exts)
        if (!strcmp(e.extensionName, XR_KHR_D3D12_ENABLE_EXTENSION_NAME)) haveD3D12 = true;
    if (!haveD3D12) {
        printf("runtime has no XR_KHR_D3D12_enable\n");
        return 1;
    }

    const char* enabled[1] = {XR_KHR_D3D12_ENABLE_EXTENSION_NAME};
    XrInstanceCreateInfo ici{XR_TYPE_INSTANCE_CREATE_INFO};
    ici.enabledExtensionCount = 1;
    ici.enabledExtensionNames = enabled;
    strcpy(ici.applicationInfo.applicationName, "GoldenEyeVR stereo");
    strcpy(ici.applicationInfo.engineName, "RT64/N64Recomp");
    ici.applicationInfo.applicationVersion = 1;
    ici.applicationInfo.engineVersion = 1;
    ici.applicationInfo.apiVersion = XR_API_VERSION_1_0; /* NOT XR_CURRENT_API_VERSION — see 09 */
    CHK(xrCreateInstance(&ici, &g_instance));

    XrSystemGetInfo sgi{XR_TYPE_SYSTEM_GET_INFO};
    sgi.formFactor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;
    XrSystemId systemId = XR_NULL_SYSTEM_ID;
    CHK(xrGetSystem(g_instance, &sgi, &systemId));

    uint32_t viewCount = 0;
    CHK(xrEnumerateViewConfigurationViews(g_instance, systemId,
                                          XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, 0, &viewCount, nullptr));
    std::vector<XrViewConfigurationView> viewCfgs(viewCount, {XR_TYPE_VIEW_CONFIGURATION_VIEW});
    CHK(xrEnumerateViewConfigurationViews(g_instance, systemId,
                                          XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, viewCount,
                                          &viewCount, viewCfgs.data()));
    if (viewCount != 2) {
        printf("expected 2 views, got %u\n", viewCount);
        return 1;
    }

    uint32_t blendCount = 0;
    CHK(xrEnumerateEnvironmentBlendModes(g_instance, systemId,
                                         XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, 0, &blendCount, nullptr));
    std::vector<XrEnvironmentBlendMode> blends(blendCount);
    CHK(xrEnumerateEnvironmentBlendModes(g_instance, systemId,
                                         XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, blendCount,
                                         &blendCount, blends.data()));

    /* ---------------- D3D12 on the runtime's adapter ---------------- */
    PFN_xrGetD3D12GraphicsRequirementsKHR pfnGetReq = nullptr;
    CHK(xrGetInstanceProcAddr(g_instance, "xrGetD3D12GraphicsRequirementsKHR",
                              (PFN_xrVoidFunction*) &pfnGetReq));
    XrGraphicsRequirementsD3D12KHR req{XR_TYPE_GRAPHICS_REQUIREMENTS_D3D12_KHR};
    CHK(pfnGetReq(g_instance, systemId, &req));

    IDXGIFactory4* factory = nullptr;
    HCHK(CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**) &factory));
    IDXGIAdapter1* adapter = nullptr;
    for (UINT i = 0; factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; i++) {
        DXGI_ADAPTER_DESC1 d{};
        adapter->GetDesc1(&d);
        if (d.AdapterLuid.LowPart == req.adapterLuid.LowPart &&
            d.AdapterLuid.HighPart == req.adapterLuid.HighPart)
            break;
        adapter->Release();
        adapter = nullptr;
    }
    if (!adapter) {
        printf("runtime's adapter not found\n");
        return 1;
    }

    ID3D12Device* dev = nullptr;
    HCHK(D3D12CreateDevice(adapter, req.minFeatureLevel, __uuidof(ID3D12Device), (void**) &dev));
    D3D12_COMMAND_QUEUE_DESC qd{};
    qd.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    ID3D12CommandQueue* queue = nullptr;
    HCHK(dev->CreateCommandQueue(&qd, __uuidof(ID3D12CommandQueue), (void**) &queue));

    /* ---------------- session ---------------- */
    XrGraphicsBindingD3D12KHR binding{XR_TYPE_GRAPHICS_BINDING_D3D12_KHR};
    binding.device = dev;
    binding.queue = queue;
    XrSessionCreateInfo sci{XR_TYPE_SESSION_CREATE_INFO};
    sci.next = &binding;
    sci.systemId = systemId;
    XrSession session = XR_NULL_HANDLE;
    CHK(xrCreateSession(g_instance, &sci, &session));

    XrReferenceSpaceCreateInfo rsci{XR_TYPE_REFERENCE_SPACE_CREATE_INFO};
    rsci.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
    rsci.poseInReferenceSpace.orientation.w = 1.0f;
    XrSpace space = XR_NULL_HANDLE;
    if (XR_FAILED(xrCreateReferenceSpace(session, &rsci, &space))) {
        /* STAGE needs room setup; LOCAL always exists and is head-relative. */
        rsci.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_LOCAL;
        CHK(xrCreateReferenceSpace(session, &rsci, &space));
        printf("note: STAGE unavailable, using LOCAL (floor will be at head height)\n");
    }

    /* ---------------- swapchains ---------------- */
    uint32_t fmtCount = 0;
    CHK(xrEnumerateSwapchainFormats(session, 0, &fmtCount, nullptr));
    std::vector<int64_t> formats(fmtCount);
    CHK(xrEnumerateSwapchainFormats(session, fmtCount, &fmtCount, formats.data()));

    int64_t chosen = 0;
    const int64_t prefer[] = {DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
                              DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_B8G8R8A8_UNORM};
    for (int64_t p : prefer) {
        for (int64_t f : formats)
            if (f == p) { chosen = p; break; }
        if (chosen) break;
    }
    if (!chosen) chosen = formats[0];
    printf("swapchain format : %lld\n", (long long) chosen);

    EyeTarget eyes[2];
    for (int i = 0; i < 2; i++) {
        EyeTarget& e = eyes[i];
        e.w = viewCfgs[i].recommendedImageRectWidth;
        e.h = viewCfgs[i].recommendedImageRectHeight;

        XrSwapchainCreateInfo scinfo{XR_TYPE_SWAPCHAIN_CREATE_INFO};
        scinfo.usageFlags = XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT;
        scinfo.format = chosen;
        scinfo.sampleCount = 1;
        scinfo.width = e.w;
        scinfo.height = e.h;
        scinfo.faceCount = 1;
        scinfo.arraySize = 1;
        scinfo.mipCount = 1;
        CHK(xrCreateSwapchain(session, &scinfo, &e.swapchain));

        uint32_t imgCount = 0;
        CHK(xrEnumerateSwapchainImages(e.swapchain, 0, &imgCount, nullptr));
        e.images.assign(imgCount, {XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR});
        CHK(xrEnumerateSwapchainImages(e.swapchain, imgCount, &imgCount,
                                       (XrSwapchainImageBaseHeader*) e.images.data()));

        D3D12_DESCRIPTOR_HEAP_DESC hd{};
        hd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        hd.NumDescriptors = imgCount;
        HCHK(dev->CreateDescriptorHeap(&hd, __uuidof(ID3D12DescriptorHeap), (void**) &e.rtvHeap));

        const UINT rtvSize = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        D3D12_CPU_DESCRIPTOR_HANDLE h = e.rtvHeap->GetCPUDescriptorHandleForHeapStart();
        for (uint32_t k = 0; k < imgCount; k++) {
            D3D12_RENDER_TARGET_VIEW_DESC rd{};
            rd.Format = (DXGI_FORMAT) chosen;
            rd.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
            dev->CreateRenderTargetView(e.images[k].texture, &rd, h);
            h.ptr += rtvSize;
        }

        D3D12_HEAP_PROPERTIES hp{};
        hp.Type = D3D12_HEAP_TYPE_DEFAULT;
        D3D12_RESOURCE_DESC rdz{};
        rdz.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        rdz.Width = e.w;
        rdz.Height = e.h;
        rdz.DepthOrArraySize = 1;
        rdz.MipLevels = 1;
        rdz.Format = DXGI_FORMAT_D32_FLOAT;
        rdz.SampleDesc.Count = 1;
        rdz.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
        D3D12_CLEAR_VALUE cv{};
        cv.Format = DXGI_FORMAT_D32_FLOAT;
        cv.DepthStencil.Depth = 1.0f;
        HCHK(dev->CreateCommittedResource(&hp, D3D12_HEAP_FLAG_NONE, &rdz,
                                          D3D12_RESOURCE_STATE_DEPTH_WRITE, &cv,
                                          __uuidof(ID3D12Resource), (void**) &e.depth));

        D3D12_DESCRIPTOR_HEAP_DESC dhd{};
        dhd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
        dhd.NumDescriptors = 1;
        HCHK(dev->CreateDescriptorHeap(&dhd, __uuidof(ID3D12DescriptorHeap), (void**) &e.dsvHeap));
        dev->CreateDepthStencilView(e.depth, nullptr, e.dsvHeap->GetCPUDescriptorHandleForHeapStart());

        printf("eye %d swapchain : %u x %u, %u images\n", i, e.w, e.h, imgCount);
    }

    /* ---------------- pipeline ---------------- */
    D3D12_ROOT_PARAMETER rp{};
    rp.ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
    rp.Constants.Num32BitValues = 16;
    rp.ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
    D3D12_ROOT_SIGNATURE_DESC rsd{};
    rsd.NumParameters = 1;
    rsd.pParameters = &rp;
    rsd.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

    ID3DBlob* rsBlob = nullptr;
    ID3DBlob* errBlob = nullptr;
    if (FAILED(D3D12SerializeRootSignature(&rsd, D3D_ROOT_SIGNATURE_VERSION_1, &rsBlob, &errBlob))) {
        printf("root sig: %s\n", errBlob ? (char*) errBlob->GetBufferPointer() : "?");
        return 1;
    }
    ID3D12RootSignature* rootSig = nullptr;
    HCHK(dev->CreateRootSignature(0, rsBlob->GetBufferPointer(), rsBlob->GetBufferSize(),
                                  __uuidof(ID3D12RootSignature), (void**) &rootSig));

    ID3DBlob* vs = nullptr;
    ID3DBlob* ps = nullptr;
    if (FAILED(D3DCompile(kShader, strlen(kShader), nullptr, nullptr, nullptr, "VSMain", "vs_5_0", 0, 0, &vs, &errBlob))) {
        printf("VS: %s\n", errBlob ? (char*) errBlob->GetBufferPointer() : "?");
        return 1;
    }
    if (FAILED(D3DCompile(kShader, strlen(kShader), nullptr, nullptr, nullptr, "PSMain", "ps_5_0", 0, 0, &ps, &errBlob))) {
        printf("PS: %s\n", errBlob ? (char*) errBlob->GetBufferPointer() : "?");
        return 1;
    }

    D3D12_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
    };

    D3D12_GRAPHICS_PIPELINE_STATE_DESC pso{};
    pso.pRootSignature = rootSig;
    pso.VS = {vs->GetBufferPointer(), vs->GetBufferSize()};
    pso.PS = {ps->GetBufferPointer(), ps->GetBufferSize()};
    pso.InputLayout = {layout, 2};
    pso.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
    pso.NumRenderTargets = 1;
    pso.RTVFormats[0] = (DXGI_FORMAT) chosen;
    pso.DSVFormat = DXGI_FORMAT_D32_FLOAT;
    pso.SampleDesc.Count = 1;
    pso.SampleMask = UINT_MAX;
    pso.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
    pso.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
    pso.RasterizerState.DepthClipEnable = TRUE;
    pso.DepthStencilState.DepthEnable = TRUE;
    pso.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
    pso.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
    for (int i = 0; i < 8; i++) {
        pso.BlendState.RenderTarget[i].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
    }
    ID3D12PipelineState* pipeline = nullptr;
    HCHK(dev->CreateGraphicsPipelineState(&pso, __uuidof(ID3D12PipelineState), (void**) &pipeline));

    /* ---------------- vertex buffer ---------------- */
    std::vector<Vtx> world = buildWorld();
    const UINT vbBytes = (UINT) (world.size() * sizeof(Vtx));

    D3D12_HEAP_PROPERTIES uhp{};
    uhp.Type = D3D12_HEAP_TYPE_UPLOAD;
    D3D12_RESOURCE_DESC vbd{};
    vbd.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    vbd.Width = vbBytes;
    vbd.Height = 1;
    vbd.DepthOrArraySize = 1;
    vbd.MipLevels = 1;
    vbd.Format = DXGI_FORMAT_UNKNOWN;
    vbd.SampleDesc.Count = 1;
    vbd.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    ID3D12Resource* vb = nullptr;
    HCHK(dev->CreateCommittedResource(&uhp, D3D12_HEAP_FLAG_NONE, &vbd,
                                      D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
                                      __uuidof(ID3D12Resource), (void**) &vb));
    void* mapped = nullptr;
    D3D12_RANGE noRead{0, 0};
    HCHK(vb->Map(0, &noRead, &mapped));
    memcpy(mapped, world.data(), vbBytes);
    vb->Unmap(0, nullptr);

    D3D12_VERTEX_BUFFER_VIEW vbv{};
    vbv.BufferLocation = vb->GetGPUVirtualAddress();
    vbv.SizeInBytes = vbBytes;
    vbv.StrideInBytes = sizeof(Vtx);

    ID3D12CommandAllocator* alloc = nullptr;
    HCHK(dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
                                     __uuidof(ID3D12CommandAllocator), (void**) &alloc));
    ID3D12GraphicsCommandList* cl = nullptr;
    HCHK(dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, alloc, nullptr,
                                __uuidof(ID3D12GraphicsCommandList), (void**) &cl));
    cl->Close();

    ID3D12Fence* fence = nullptr;
    HCHK(dev->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(ID3D12Fence), (void**) &fence));
    UINT64 fenceVal = 0;
    HANDLE fenceEvt = CreateEventW(nullptr, FALSE, FALSE, nullptr);

    printf("\n%zu vertices (%zu lines). Put the headset on.\n\n", world.size(), world.size() / 2);

    /* ---------------- frame loop ---------------- */
    bool running = false, exiting = false, printedOnce = false;
    XrSessionState state = XR_SESSION_STATE_UNKNOWN;
    int framesRendered = 0;

    /* EYE TINT (run with "tint" as argv[1]): clears the left eye to dark red and
     * the right to dark blue. This is the unambiguous test for "are the two eyes
     * actually receiving different images". Judging that from parallax alone is
     * unreliable — disparity shrinks with distance, so a correct stereo scene of
     * distant objects can look monoscopic, and a genuinely monoscopic scene still
     * looks like a convincing 3D room. A full-screen colour cannot be missed and
     * cannot be faked by correct perspective. */
    bool tint = false;
    {
        int argc = 0;
        LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
        for (int i = 1; i < argc; i++)
            if (!wcscmp(argv[i], L"tint")) tint = true;
        if (argv) LocalFree(argv);
    }
    printf("eye tint: %s\n", tint ? "ON (left=red, right=blue)" : "off");

    /* SCENE ANCHOR. The scene was authored around a floor at y=0, but this rig
     * reports the head 2.5-3.2 m up — a floor-calibration offset, not a tracking
     * fault (x/z are stable to centimetres). Rendering the scene at absolute
     * STAGE coordinates therefore puts every test object far below and far away,
     * which collapses exactly the disparity the test exists to measure.
     *
     * So the scene is pinned to wherever the head was on the first rendered
     * frame: local y=1 lands at eye height, and the depth cubes sit 1/2/4/8 m
     * straight ahead of where the wearer was looking from. That makes the near
     * cube genuinely near, which is the whole point. */
    bool anchored = false;
    M4 model = m4identity();

    while (!exiting) {
        for (;;) {
            XrEventDataBuffer ev{XR_TYPE_EVENT_DATA_BUFFER};
            XrResult r = xrPollEvent(g_instance, &ev);
            if (r == XR_EVENT_UNAVAILABLE || XR_FAILED(r)) break;
            if (ev.type == XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED) {
                state = reinterpret_cast<XrEventDataSessionStateChanged*>(&ev)->state;
                if (state == XR_SESSION_STATE_READY && !running) {
                    XrSessionBeginInfo bi{XR_TYPE_SESSION_BEGIN_INFO};
                    bi.primaryViewConfigurationType = XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO;
                    CHK(xrBeginSession(session, &bi));
                    running = true;
                    printf("session running.\n");
                } else if (state == XR_SESSION_STATE_STOPPING) {
                    xrEndSession(session);
                    running = false;
                    exiting = true;
                } else if (state == XR_SESSION_STATE_EXITING || state == XR_SESSION_STATE_LOSS_PENDING) {
                    exiting = true;
                }
            }
        }
        if (exiting) break;
        if (!running) { Sleep(20); continue; }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) break;

        XrFrameState fs{XR_TYPE_FRAME_STATE};
        XrFrameWaitInfo fwi{XR_TYPE_FRAME_WAIT_INFO};
        CHK(xrWaitFrame(session, &fwi, &fs));
        XrFrameBeginInfo fbi{XR_TYPE_FRAME_BEGIN_INFO};
        CHK(xrBeginFrame(session, &fbi));

        XrCompositionLayerProjectionView projViews[2]{};
        XrCompositionLayerProjection layer{XR_TYPE_COMPOSITION_LAYER_PROJECTION};
        bool haveLayer = false;

        if (fs.shouldRender) {
            XrViewLocateInfo vli{XR_TYPE_VIEW_LOCATE_INFO};
            vli.viewConfigurationType = XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO;
            vli.displayTime = fs.predictedDisplayTime;
            vli.space = space;
            XrViewState vst{XR_TYPE_VIEW_STATE};
            uint32_t got = 0;
            XrView views[2] = {{XR_TYPE_VIEW}, {XR_TYPE_VIEW}};
            XrResult lr = xrLocateViews(session, &vli, &vst, 2, &got, views);

            if (XR_SUCCEEDED(lr) && got == 2 &&
                (vst.viewStateFlags & XR_VIEW_STATE_ORIENTATION_VALID_BIT) &&
                (vst.viewStateFlags & XR_VIEW_STATE_POSITION_VALID_BIT)) {

                WaitForSingleObject(fenceEvt, 0);
                if (fence->GetCompletedValue() < fenceVal) {
                    fence->SetEventOnCompletion(fenceVal, fenceEvt);
                    WaitForSingleObject(fenceEvt, INFINITE);
                }
                /* Re-anchor every frame until the session is FOCUSED, then lock.
                 *
                 * Anchoring on the first rendered frame was wrong: frames render
                 * as soon as the session is VISIBLE, which happens while the
                 * headset is still in the wearer's hand. The first run anchored
                 * at y=2.42 while the wearer settled at y=3.19, leaving the whole
                 * scene 0.8 m below eye level. FOCUSED is the state that actually
                 * means "being worn and receiving input", so that is the correct
                 * moment to freeze the scene position. */
                if (!anchored) {
                    const XrVector3f& hp = views[0].pose.position;
                    model = m4identity();
                    model.m[3][0] = hp.x;
                    model.m[3][1] = hp.y - 1.0f; /* scene's y=1 -> eye height */
                    model.m[3][2] = hp.z;
                    if (state == XR_SESSION_STATE_FOCUSED) {
                        anchored = true;
                        printf("scene ANCHORED (focused) at %.3f %.3f %.3f\n", hp.x, hp.y, hp.z);
                    }
                }

                alloc->Reset();
                cl->Reset(alloc, pipeline);
                cl->SetGraphicsRootSignature(rootSig);
                cl->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
                cl->IASetVertexBuffers(0, 1, &vbv);

                for (int i = 0; i < 2; i++) {
                    EyeTarget& e = eyes[i];
                    uint32_t idx = 0;
                    XrSwapchainImageAcquireInfo ai{XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO};
                    CHK(xrAcquireSwapchainImage(e.swapchain, &ai, &idx));
                    XrSwapchainImageWaitInfo wi{XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO};
                    wi.timeout = XR_INFINITE_DURATION;
                    CHK(xrWaitSwapchainImage(e.swapchain, &wi));

                    const UINT rtvSize = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
                    D3D12_CPU_DESCRIPTOR_HANDLE rtv = e.rtvHeap->GetCPUDescriptorHandleForHeapStart();
                    rtv.ptr += idx * rtvSize;
                    D3D12_CPU_DESCRIPTOR_HANDLE dsv = e.dsvHeap->GetCPUDescriptorHandleForHeapStart();

                    float clear[4] = {0.02f, 0.02f, 0.05f, 1.0f};
                    if (tint) {
                        clear[0] = (i == 0) ? 0.25f : 0.02f;
                        clear[2] = (i == 0) ? 0.02f : 0.30f;
                    }
                    cl->OMSetRenderTargets(1, &rtv, FALSE, &dsv);
                    cl->ClearRenderTargetView(rtv, clear, 0, nullptr);
                    cl->ClearDepthStencilView(dsv, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

                    D3D12_VIEWPORT vp{0.0f, 0.0f, (float) e.w, (float) e.h, 0.0f, 1.0f};
                    D3D12_RECT sr{0, 0, (LONG) e.w, (LONG) e.h};
                    cl->RSSetViewports(1, &vp);
                    cl->RSSetScissorRects(1, &sr);

                    const XrFovf& f = views[i].fov;
                    M4 proj = m4projFromTangents(tanf(f.angleLeft), tanf(f.angleRight),
                                                 tanf(f.angleUp), tanf(f.angleDown), 0.05f, 100.0f);
                    M4 view = m4viewFromPose(views[i].pose);
                    M4 mvp = m4mul(m4mul(model, view), proj);
                    cl->SetGraphicsRoot32BitConstants(0, 16, &mvp, 0);
                    cl->DrawInstanced((UINT) world.size(), 1, 0, 0);

                    projViews[i] = {XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW};
                    projViews[i].pose = views[i].pose;
                    projViews[i].fov = views[i].fov;
                    projViews[i].subImage.swapchain = e.swapchain;
                    projViews[i].subImage.imageRect = {{0, 0}, {(int32_t) e.w, (int32_t) e.h}};
                    projViews[i].subImage.imageArrayIndex = 0;

                    if (!printedOnce) {
                        printf("eye %d  fov L%+.2f R%+.2f U%+.2f D%+.2f deg | pos %+.3f %+.3f %+.3f\n",
                               i, f.angleLeft * 57.2957795f, f.angleRight * 57.2957795f,
                               f.angleUp * 57.2957795f, f.angleDown * 57.2957795f,
                               views[i].pose.position.x, views[i].pose.position.y, views[i].pose.position.z);
                    }
                }
                printedOnce = true;

                /* Head position once a second. This is the objective record of
                 * whether position tracking is reaching the view matrix — if the
                 * numbers move when the wearer walks, it is, regardless of what
                 * the image subjectively looks like. Also reveals where the
                 * wearer is standing relative to the STAGE origin, which is what
                 * decides the apparent size ordering of the depth cubes. */
                if ((framesRendered % 90) == 0) {
                    const XrVector3f& p = views[0].pose.position;
                    printf("t+%4ds  head  x %+6.3f  y %+6.3f  z %+6.3f   (dist from origin %.2f m)\n",
                           framesRendered / 90, p.x, p.y, p.z,
                           sqrtf(p.x * p.x + p.z * p.z));
                }

                cl->Close();
                ID3D12CommandList* lists[] = {cl};
                queue->ExecuteCommandLists(1, lists);
                queue->Signal(fence, ++fenceVal);

                for (int i = 0; i < 2; i++) {
                    XrSwapchainImageReleaseInfo ri{XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO};
                    CHK(xrReleaseSwapchainImage(eyes[i].swapchain, &ri));
                }

                layer.space = space;
                layer.viewCount = 2;
                layer.views = projViews;
                haveLayer = true;
                framesRendered++;
            }
        }

        const XrCompositionLayerBaseHeader* layers[1] = {(XrCompositionLayerBaseHeader*) &layer};
        XrFrameEndInfo fei{XR_TYPE_FRAME_END_INFO};
        fei.displayTime = fs.predictedDisplayTime;
        fei.environmentBlendMode = blends[0];
        fei.layerCount = haveLayer ? 1 : 0;
        fei.layers = haveLayer ? layers : nullptr;
        CHK(xrEndFrame(session, &fei));
    }

    printf("\nrendered %d stereo frames. shutting down.\n", framesRendered);
    if (running) xrEndSession(session);
    xrDestroySpace(space);
    for (int i = 0; i < 2; i++) xrDestroySwapchain(eyes[i].swapchain);
    xrDestroySession(session);
    xrDestroyInstance(g_instance);
    return 0;
}
