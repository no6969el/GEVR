/*
 * xr_probe.cpp — GoldenEyeVR Phase 2 reconnaissance.
 *
 * Creates a real OpenXR session against whatever runtime is active, runs a few
 * frames, and prints the numbers Phase 1 has so far been guessing at:
 *
 *   - per-eye field of view, as angles AND as the tangents the patch wants
 *   - per-eye pose: position (gives IPD) and orientation (gives CANT)
 *   - recommended swapchain size per eye
 *   - supported reference spaces, blend modes, refresh rates
 *
 * It renders nothing. It submits zero composition layers. It cannot affect
 * GoldenRecomp.exe in any way — that is the entire point of doing this first.
 *
 * WHY THE ORIENTATION MATTERS, AND WHY THIS PROBE EXISTS
 * -----------------------------------------------------
 * patches/ge_vr_bindtest.c currently assumes the two eyes are PARALLEL and
 * differ only in their asymmetric frustum. That is true of a Quest 3. It is NOT
 * true of a Pimax, whose panels are physically angled outward — the runtime
 * reports each eye with a yawed pose, and a renderer that ignores that yaw
 * produces two images that do not fuse. The symptom is eye strain and a world
 * that will not sit still, not an obviously broken picture, which makes it
 * expensive to find later.
 *
 * So: read `eye yaw` in the output below. If it is ~0 for both eyes, the
 * parallel assumption holds. If it is a few degrees outward per eye, Phase 1
 * needs per-eye view ROTATION as well as per-eye projection, and the plan's
 * "step 2 = IPD offset" is understated — it is IPD *and* cant.
 *
 * BUILD (from this directory, in a VS developer shell):
 *   cl /std:c++17 /EHsc /O2 /nologo xr_probe.cpp ^
 *      /I lib\openxr\include ^
 *      /link lib\openxr\native\x64\release\lib\openxr_loader.lib ^
 *            d3d12.lib dxgi.lib
 * Then copy lib\openxr\native\x64\release\bin\openxr_loader.dll beside the exe.
 *
 * RUN: start SteamVR (or make the Oculus runtime active) and put the headset on
 * so the session reaches FOCUSED. A headset that is asleep gives poses that are
 * flagged invalid and the probe will say so rather than printing garbage.
 */
#define XR_USE_GRAPHICS_API_D3D12
#define XR_USE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>
#include <d3d12.h>
#include <dxgi1_4.h>

#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>

#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

static FILE* g_log = nullptr;

static void out(const char* fmt, ...) {
    char buf[4096];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    fputs(buf, stdout);
    if (g_log) fputs(buf, g_log);
}

static XrInstance g_instance = XR_NULL_HANDLE;

static const char* xrStr(XrResult r) {
    static char buf[XR_MAX_RESULT_STRING_SIZE];
    if (g_instance != XR_NULL_HANDLE && XR_SUCCEEDED(xrResultToString(g_instance, r, buf))) return buf;
    snprintf(buf, sizeof(buf), "XrResult(%d)", (int) r);
    return buf;
}

#define CHK(expr)                                                       \
    do {                                                                \
        XrResult _r = (expr);                                           \
        if (XR_FAILED(_r)) {                                            \
            out("\nFAILED: %s\n   -> %s\n", #expr, xrStr(_r));          \
            return 1;                                                   \
        }                                                               \
    } while (0)

static const float kPi = 3.14159265358979323846f;
static float deg(float rad) { return rad * 180.0f / kPi; }

/* Yaw about Y, in degrees. Positive = turned left. For a canted headset the two
 * eyes yaw in OPPOSITE directions, each by roughly half the total cant. */
static float quatYawDeg(const XrQuaternionf& q) {
    return deg(atan2f(2.0f * (q.w * q.y + q.x * q.z), 1.0f - 2.0f * (q.y * q.y + q.z * q.z)));
}
static float quatPitchDeg(const XrQuaternionf& q) {
    float s = 2.0f * (q.w * q.x - q.y * q.z);
    if (s > 1.0f) s = 1.0f;
    if (s < -1.0f) s = -1.0f;
    return deg(asinf(s));
}
static float quatRollDeg(const XrQuaternionf& q) {
    return deg(atan2f(2.0f * (q.w * q.z + q.x * q.y), 1.0f - 2.0f * (q.x * q.x + q.z * q.z)));
}

int main() {
    g_log = fopen("xr_probe_report.txt", "w");
    out("=== GoldenEyeVR OpenXR probe ===\n\n");

    /* ---- extensions ---------------------------------------------------- */
    uint32_t extCount = 0;
    CHK(xrEnumerateInstanceExtensionProperties(nullptr, 0, &extCount, nullptr));
    std::vector<XrExtensionProperties> exts(extCount, {XR_TYPE_EXTENSION_PROPERTIES});
    CHK(xrEnumerateInstanceExtensionProperties(nullptr, extCount, &extCount, exts.data()));

    bool haveD3D12 = false, haveRefreshRate = false;
    for (const auto& e : exts) {
        if (!strcmp(e.extensionName, XR_KHR_D3D12_ENABLE_EXTENSION_NAME)) haveD3D12 = true;
        if (!strcmp(e.extensionName, "XR_FB_display_refresh_rate")) haveRefreshRate = true;
    }
    out("runtime advertises %u extensions; D3D12=%s refresh_rate_ext=%s\n\n",
        extCount, haveD3D12 ? "yes" : "NO", haveRefreshRate ? "yes" : "no");

    if (!haveD3D12) {
        out("The active runtime does not support XR_KHR_D3D12_enable.\n"
            "RT64 can also run Vulkan (api_option in the config) — if this is the\n"
            "blocker, the session has to bind Vulkan instead. Stopping here.\n");
        return 1;
    }

    /* ---- instance ------------------------------------------------------ */
    const char* enabled[2] = {XR_KHR_D3D12_ENABLE_EXTENSION_NAME, "XR_FB_display_refresh_rate"};
    XrInstanceCreateInfo ici{XR_TYPE_INSTANCE_CREATE_INFO};
    ici.enabledExtensionCount = haveRefreshRate ? 2 : 1;
    ici.enabledExtensionNames = enabled;
    strcpy(ici.applicationInfo.applicationName, "GoldenEyeVR probe");
    ici.applicationInfo.applicationVersion = 1;
    strcpy(ici.applicationInfo.engineName, "RT64/N64Recomp");
    ici.applicationInfo.engineVersion = 1;
    /* GOTCHA: do NOT use XR_CURRENT_API_VERSION here. The 1.1.x headers define it
     * as OpenXR 1.1, and SteamVR's runtime implements 1.0 only — asking for 1.1
     * fails xrCreateInstance with XR_ERROR_API_VERSION_UNSUPPORTED (-4), which
     * the loader reports only as "chained CreateInstance call failed". Extension
     * enumeration succeeds first, because that is handled by the loader and never
     * reaches the runtime, so it looks like the runtime is fine right up until
     * instance creation. Request 1.0 and every 1.0 runtime accepts it. */
    ici.applicationInfo.apiVersion = XR_API_VERSION_1_0;
    CHK(xrCreateInstance(&ici, &g_instance));

    XrInstanceProperties ip{XR_TYPE_INSTANCE_PROPERTIES};
    CHK(xrGetInstanceProperties(g_instance, &ip));
    out("runtime          : %s  v%u.%u.%u\n", ip.runtimeName,
        (unsigned) XR_VERSION_MAJOR(ip.runtimeVersion),
        (unsigned) XR_VERSION_MINOR(ip.runtimeVersion),
        (unsigned) XR_VERSION_PATCH(ip.runtimeVersion));

    /* ---- system -------------------------------------------------------- */
    XrSystemGetInfo sgi{XR_TYPE_SYSTEM_GET_INFO};
    sgi.formFactor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;
    XrSystemId systemId = XR_NULL_SYSTEM_ID;
    CHK(xrGetSystem(g_instance, &sgi, &systemId));

    XrSystemProperties sp{XR_TYPE_SYSTEM_PROPERTIES};
    CHK(xrGetSystemProperties(g_instance, systemId, &sp));
    out("system           : %s\n", sp.systemName);
    out("max swapchain    : %u x %u, %u layers\n",
        sp.graphicsProperties.maxSwapchainImageWidth,
        sp.graphicsProperties.maxSwapchainImageHeight,
        sp.graphicsProperties.maxLayerCount);
    out("orientation/pos  : %s / %s tracking\n\n",
        sp.trackingProperties.orientationTracking ? "yes" : "no",
        sp.trackingProperties.positionTracking ? "yes" : "no");

    /* ---- view configuration -------------------------------------------- */
    uint32_t viewCount = 0;
    CHK(xrEnumerateViewConfigurationViews(g_instance, systemId,
                                          XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO,
                                          0, &viewCount, nullptr));
    std::vector<XrViewConfigurationView> viewCfgs(viewCount, {XR_TYPE_VIEW_CONFIGURATION_VIEW});
    CHK(xrEnumerateViewConfigurationViews(g_instance, systemId,
                                          XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO,
                                          viewCount, &viewCount, viewCfgs.data()));
    out("PRIMARY_STEREO has %u views\n", viewCount);
    for (uint32_t i = 0; i < viewCount; i++) {
        out("  view %u recommended %u x %u (max %u x %u), %u samples\n", i,
            viewCfgs[i].recommendedImageRectWidth, viewCfgs[i].recommendedImageRectHeight,
            viewCfgs[i].maxImageRectWidth, viewCfgs[i].maxImageRectHeight,
            viewCfgs[i].recommendedSwapchainSampleCount);
    }
    out("\n");

    /* ---- blend modes --------------------------------------------------- */
    uint32_t blendCount = 0;
    CHK(xrEnumerateEnvironmentBlendModes(g_instance, systemId,
                                         XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO,
                                         0, &blendCount, nullptr));
    std::vector<XrEnvironmentBlendMode> blends(blendCount);
    CHK(xrEnumerateEnvironmentBlendModes(g_instance, systemId,
                                         XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO,
                                         blendCount, &blendCount, blends.data()));
    XrEnvironmentBlendMode blendMode = blends[0];
    out("blend modes      : %u (using first, enum %d)\n\n", blendCount, (int) blendMode);

    /* ---- D3D12 device matching the runtime's adapter -------------------- */
    PFN_xrGetD3D12GraphicsRequirementsKHR pfnGetReq = nullptr;
    CHK(xrGetInstanceProcAddr(g_instance, "xrGetD3D12GraphicsRequirementsKHR",
                              (PFN_xrVoidFunction*) &pfnGetReq));

    XrGraphicsRequirementsD3D12KHR req{XR_TYPE_GRAPHICS_REQUIREMENTS_D3D12_KHR};
    CHK(pfnGetReq(g_instance, systemId, &req));
    out("runtime wants adapter LUID %08lx:%08lx, feature level 0x%x\n",
        (unsigned long) req.adapterLuid.HighPart, (unsigned long) req.adapterLuid.LowPart,
        (unsigned) req.minFeatureLevel);

    IDXGIFactory4* factory = nullptr;
    if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**) &factory))) {
        out("CreateDXGIFactory1 failed\n");
        return 1;
    }
    IDXGIAdapter1* adapter = nullptr;
    for (UINT i = 0; factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; i++) {
        DXGI_ADAPTER_DESC1 d{};
        adapter->GetDesc1(&d);
        if (d.AdapterLuid.LowPart == req.adapterLuid.LowPart &&
            d.AdapterLuid.HighPart == req.adapterLuid.HighPart) {
            char name[256];
            WideCharToMultiByte(CP_UTF8, 0, d.Description, -1, name, sizeof(name), nullptr, nullptr);
            out("adapter          : %s\n\n", name);
            break;
        }
        adapter->Release();
        adapter = nullptr;
    }
    if (!adapter) {
        out("Could not find the adapter the runtime asked for. On a laptop or a\n"
            "multi-GPU rig this means the headset is on a different GPU than the\n"
            "default one — RT64 would have to be told to use the same adapter.\n");
        return 1;
    }

    ID3D12Device* device = nullptr;
    if (FAILED(D3D12CreateDevice(adapter, req.minFeatureLevel, __uuidof(ID3D12Device),
                                 (void**) &device))) {
        out("D3D12CreateDevice failed at the runtime's minimum feature level\n");
        return 1;
    }
    D3D12_COMMAND_QUEUE_DESC qd{};
    qd.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    ID3D12CommandQueue* queue = nullptr;
    if (FAILED(device->CreateCommandQueue(&qd, __uuidof(ID3D12CommandQueue), (void**) &queue))) {
        out("CreateCommandQueue failed\n");
        return 1;
    }

    /* ---- session -------------------------------------------------------- */
    XrGraphicsBindingD3D12KHR binding{XR_TYPE_GRAPHICS_BINDING_D3D12_KHR};
    binding.device = device;
    binding.queue = queue;

    XrSessionCreateInfo sci{XR_TYPE_SESSION_CREATE_INFO};
    sci.next = &binding;
    sci.systemId = systemId;
    XrSession session = XR_NULL_HANDLE;
    CHK(xrCreateSession(g_instance, &sci, &session));
    out("session created.\n");

    /* ---- reference spaces ----------------------------------------------- */
    uint32_t spaceCount = 0;
    CHK(xrEnumerateReferenceSpaces(session, 0, &spaceCount, nullptr));
    std::vector<XrReferenceSpaceType> spaceTypes(spaceCount);
    CHK(xrEnumerateReferenceSpaces(session, spaceCount, &spaceCount, spaceTypes.data()));
    out("reference spaces : ");
    bool haveStage = false;
    for (auto s : spaceTypes) {
        const char* n = s == XR_REFERENCE_SPACE_TYPE_VIEW    ? "VIEW"
                        : s == XR_REFERENCE_SPACE_TYPE_LOCAL ? "LOCAL"
                        : s == XR_REFERENCE_SPACE_TYPE_STAGE ? "STAGE"
                                                             : "other";
        if (s == XR_REFERENCE_SPACE_TYPE_STAGE) haveStage = true;
        out("%s ", n);
    }
    out("\n\n");
    (void) haveStage;

    XrReferenceSpaceCreateInfo rsci{XR_TYPE_REFERENCE_SPACE_CREATE_INFO};
    rsci.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_LOCAL;
    rsci.poseInReferenceSpace.orientation.w = 1.0f;
    XrSpace localSpace = XR_NULL_HANDLE;
    CHK(xrCreateReferenceSpace(session, &rsci, &localSpace));

    /* ---- refresh rates --------------------------------------------------- */
    if (haveRefreshRate) {
        PFN_xrVoidFunction fn = nullptr;
        if (XR_SUCCEEDED(xrGetInstanceProcAddr(g_instance, "xrEnumerateDisplayRefreshRatesFB", &fn)) && fn) {
            typedef XrResult(XRAPI_PTR * PFN_Enum)(XrSession, uint32_t, uint32_t*, float*);
            PFN_Enum e = (PFN_Enum) fn;
            uint32_t n = 0;
            if (XR_SUCCEEDED(e(session, 0, &n, nullptr)) && n) {
                std::vector<float> rates(n);
                e(session, n, &n, rates.data());
                out("refresh rates    : ");
                for (uint32_t i = 0; i < n; i++) out("%.0f ", rates[i]);
                out("Hz\n\n");
            }
        }
    }

    /* ---- frame loop until we get valid views ----------------------------- */
    out("waiting for the session to reach a running state — put the headset on...\n");

    bool running = false, exiting = false, gotViews = false;
    XrView views[2] = {{XR_TYPE_VIEW}, {XR_TYPE_VIEW}};
    XrSessionState state = XR_SESSION_STATE_UNKNOWN;

    for (int frame = 0; frame < 3000 && !gotViews && !exiting; frame++) {
        /* events */
        for (;;) {
            XrEventDataBuffer ev{XR_TYPE_EVENT_DATA_BUFFER};
            XrResult r = xrPollEvent(g_instance, &ev);
            if (r == XR_EVENT_UNAVAILABLE) break;
            if (XR_FAILED(r)) break;
            if (ev.type == XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED) {
                auto* ssc = reinterpret_cast<XrEventDataSessionStateChanged*>(&ev);
                state = ssc->state;
                if (state == XR_SESSION_STATE_READY && !running) {
                    XrSessionBeginInfo bi{XR_TYPE_SESSION_BEGIN_INFO};
                    bi.primaryViewConfigurationType = XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO;
                    CHK(xrBeginSession(session, &bi));
                    running = true;
                    out("session state -> READY, began.\n");
                } else if (state == XR_SESSION_STATE_STOPPING) {
                    xrEndSession(session);
                    running = false;
                    exiting = true;
                } else if (state == XR_SESSION_STATE_EXITING ||
                           state == XR_SESSION_STATE_LOSS_PENDING) {
                    exiting = true;
                }
            } else if (ev.type == XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING) {
                exiting = true;
            }
        }

        if (!running) {
            Sleep(20);
            continue;
        }

        XrFrameState fs{XR_TYPE_FRAME_STATE};
        XrFrameWaitInfo fwi{XR_TYPE_FRAME_WAIT_INFO};
        CHK(xrWaitFrame(session, &fwi, &fs));

        XrFrameBeginInfo fbi{XR_TYPE_FRAME_BEGIN_INFO};
        CHK(xrBeginFrame(session, &fbi));

        if (fs.shouldRender) {
            XrViewLocateInfo vli{XR_TYPE_VIEW_LOCATE_INFO};
            vli.viewConfigurationType = XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO;
            vli.displayTime = fs.predictedDisplayTime;
            vli.space = localSpace;

            XrViewState vs{XR_TYPE_VIEW_STATE};
            uint32_t got = 0;
            XrView tmp[2] = {{XR_TYPE_VIEW}, {XR_TYPE_VIEW}};
            XrResult r = xrLocateViews(session, &vli, &vs, 2, &got, tmp);

            if (XR_SUCCEEDED(r) && got == 2 &&
                (vs.viewStateFlags & XR_VIEW_STATE_ORIENTATION_VALID_BIT) &&
                (vs.viewStateFlags & XR_VIEW_STATE_POSITION_VALID_BIT)) {
                views[0] = tmp[0];
                views[1] = tmp[1];
                gotViews = true;
                out("got valid views on frame %d (predicted period %.3f ms)\n\n",
                    frame, fs.predictedDisplayPeriod / 1e6);
            }
        }

        XrFrameEndInfo fei{XR_TYPE_FRAME_END_INFO};
        fei.displayTime = fs.predictedDisplayTime;
        fei.environmentBlendMode = blendMode;
        fei.layerCount = 0;
        fei.layers = nullptr;
        CHK(xrEndFrame(session, &fei));
    }

    if (!gotViews) {
        out("\nNever got a pose flagged both orientation- and position-valid.\n"
            "Usual cause: the headset is asleep, on standby, or not being worn.\n"
            "The session reached state %d. Wake it and run again.\n", (int) state);
    } else {
        out("=== THE NUMBERS ===\n\n");
        const char* eyeName[2] = {"LEFT ", "RIGHT"};
        float tans[2][4];

        for (int i = 0; i < 2; i++) {
            const XrFovf& f = views[i].fov;
            const XrPosef& p = views[i].pose;
            tans[i][0] = tanf(f.angleLeft);
            tans[i][1] = tanf(f.angleRight);
            tans[i][2] = tanf(f.angleUp);
            tans[i][3] = tanf(f.angleDown);

            out("%s fov  L %+7.2f deg  R %+7.2f  U %+7.2f  D %+7.2f   (H %.1f, V %.1f)\n",
                eyeName[i], deg(f.angleLeft), deg(f.angleRight), deg(f.angleUp), deg(f.angleDown),
                deg(f.angleRight - f.angleLeft), deg(f.angleUp - f.angleDown));
            out("%s tan  L %+7.4f      R %+7.4f  U %+7.4f  D %+7.4f\n",
                eyeName[i], tans[i][0], tans[i][1], tans[i][2], tans[i][3]);
            out("%s pos  x %+7.4f  y %+7.4f  z %+7.4f  (metres)\n",
                eyeName[i], p.position.x, p.position.y, p.position.z);
            out("%s rot  yaw %+7.3f  pitch %+7.3f  roll %+7.3f  (degrees)\n\n",
                eyeName[i], quatYawDeg(p.orientation), quatPitchDeg(p.orientation),
                quatRollDeg(p.orientation));
        }

        float dx = views[1].pose.position.x - views[0].pose.position.x;
        float dy = views[1].pose.position.y - views[0].pose.position.y;
        float dz = views[1].pose.position.z - views[0].pose.position.z;
        float ipd = sqrtf(dx * dx + dy * dy + dz * dz);
        float yawL = quatYawDeg(views[0].pose.orientation);
        float yawR = quatYawDeg(views[1].pose.orientation);
        float cant = yawL - yawR;

        out("IPD              : %.1f mm\n", ipd * 1000.0f);
        out("eye yaw L/R      : %+.3f / %+.3f degrees\n", yawL, yawR);
        out("total cant       : %.3f degrees\n\n", cant);

        if (fabsf(cant) < 0.5f) {
            out("VERDICT: eyes are PARALLEL (cant under half a degree).\n"
                "  The current parallel-eye assumption in ge_vr_bindtest.c holds.\n"
                "  Per-eye projection + an IPD offset is sufficient.\n\n");
        } else {
            out("VERDICT: eyes are CANTED by %.2f degrees.\n"
                "  ge_vr_bindtest.c's parallel-eye assumption DOES NOT HOLD.\n"
                "  Each eye's view matrix needs its own yaw rotation as well as its\n"
                "  own IPD offset and frustum, or the two images will not fuse.\n"
                "  This makes Phase 1 step 2 'IPD and cant', not 'IPD'.\n\n");
        }

        out("=== PASTE INTO patches/ge_vr_bindtest.c ===\n\n");
        out("GeVrEyeParams g_geVrEyeParams[2] = {\n");
        out("    /* LEFT  */ { %+.4ff, %+.4ff, %+.4ff, %+.4ff },\n",
            tans[0][0], tans[0][1], tans[0][2], tans[0][3]);
        out("    /* RIGHT */ { %+.4ff, %+.4ff, %+.4ff, %+.4ff },\n",
            tans[1][0], tans[1][1], tans[1][2], tans[1][3]);
        out("};\n\n");
        out("(measured on %s, IPD %.1f mm — these are THIS headset at THIS IPD\n"
            " setting, which is exactly why the real thing must query the runtime\n"
            " rather than bake constants.)\n\n", sp.systemName, ipd * 1000.0f);
    }

    if (running) xrEndSession(session);
    xrDestroySpace(localSpace);
    xrDestroySession(session);
    xrDestroyInstance(g_instance);
    queue->Release();
    device->Release();
    adapter->Release();
    factory->Release();

    out("done. report written to xr_probe_report.txt\n");
    if (g_log) fclose(g_log);
    return 0;
}
