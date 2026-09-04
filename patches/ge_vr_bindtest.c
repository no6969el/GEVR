/*
 * ge_vr_bindtest.c — the VR projection hook for cblock85/GoldenEye64Recomp.
 *
 * Phase 0 (bind test) PASSED on 2026-08-22. This file has since grown Phase 1
 * step 1: a real per-eye asymmetric frustum, built in place of the game's
 * symmetric one, still rendering a single eye to the monitor.
 *
 * The filename is kept for continuity with the handoff docs and diffs. It is
 * no longer only a bind test. Rename when ge_vr is split into its own repo.
 *
 * ---------------------------------------------------------------------------
 * WHAT THIS DOES NOW (GE_VR_MODE_STEREO, the default)
 * ---------------------------------------------------------------------------
 * The game builds a symmetric perspective matrix with guPerspectiveF and hands
 * it to currentPlayerSetProjectionMatrix{,F}. We replace the parts of it that
 * describe the frustum with a per-eye asymmetric one:
 *
 *   [0][0] = 2 / (tanRight - tanLeft)      horizontal scale
 *   [1][1] = 2 / (tanUp    - tanDown)      vertical scale
 *   [2][0] = (tanRight + tanLeft) / (tanRight - tanLeft)     horizontal skew
 *   [2][1] = (tanUp    + tanDown) / (tanUp    - tanDown)     vertical skew
 *   [2][2] = (n + f) / (n - f)             with n clamped up to MIN_ZNEAR
 *   [3][2] = 2nf / (n - f)                 likewise
 *
 * Row-vector convention, matching guPerspectiveF: the skew terms live in row 2,
 * not column 2. Getting that transposed is the single easiest way to produce a
 * sheared world that looks almost right, so it is written out above explicitly.
 *
 * Note that n cancels out of [0][0] and [1][1]. Clamping znear therefore costs
 * nothing in field of view — it only spends depth precision better.
 *
 * ---------------------------------------------------------------------------
 * WHAT THIS DELIBERATELY DOES NOT DO
 * ---------------------------------------------------------------------------
 * - No IPD offset. That belongs on the VIEW matrix, which this hook never sees.
 *   With one eye on a monitor an IPD shift is invisible anyway. Phase 1 step 2.
 * - No OpenXR. The eye tangents below are plausible Quest-3 constants, not
 *   runtime-queried ones. geVrGetEyeParams() is the ONE seam where a host
 *   import replaces them later — see the comment on it.
 * - No second render target. That is the genuinely unsolved part of Phase 1
 *   and nothing here pretends otherwise.
 *
 * ---------------------------------------------------------------------------
 * WHY TANGENTS AND NOT ANGLES
 * ---------------------------------------------------------------------------
 * This file is compiled into the game's MIPS address space, where libm is not
 * dependably available (the same reason Phase 0 scaled cot directly instead of
 * recovering the angle with atan). OpenXR hands out XrFovf in radians; the host
 * bridge will call tanf on those four angles natively and pass tangents across.
 * Nothing in here ever needs trig.
 *
 * Sign convention follows XrFovf: left and down are negative, right and up
 * positive. So a symmetric 90-degree eye is {-1, +1, +1, -1}.
 *
 * ---------------------------------------------------------------------------
 * PHASE 0 RESULT (2026-08-22, first run on Windows) — kept for the record
 * ---------------------------------------------------------------------------
 * At GE_BT_COT_SCALE = 0.3 the world visibly widened. The hook reaches the
 * world projection; VR-PLAN's attachment model is sound.
 *
 * It also widened the menus, which answers a question Phase 0 did not ask.
 * viSetupCurrentPlayerView is the SINGLE caller of both setters (confirmed by
 * scanning all 60 RecompiledFuncs translation units), and menus are drawn
 * through the same player view, so there is no narrower hook to move to. The
 * separation has to come from game state instead, which is what geVrInLevel()
 * does. That is good news for VR: one chokepoint governs the whole world
 * projection.
 *
 * WHY THE SETTERS AND NOT THE GETTERS: the getters run many times per frame
 * (bg.c:692, :729 and six more, sky.c:811, bondview2.c:8244), so mutating there
 * compounds within a frame and collapses the FOV to black. The setters run
 * exactly once per frame from src/fr.c:720-721, right after guPerspectiveF
 * rebuilds the matrix, so mutating there is idempotent by construction. Both
 * setters are one-line assignments in the decomp (bondview.c:802 and :828), so
 * replacing them wholesale via RECOMP_PATCH loses no original behaviour.
 */
#include "patches.h"

/* --- modes ---------------------------------------------------------------- *
 * OFF      compiles the patch in but leaves the image untouched. The call
 *          counters still increment, which is the whole point: it is the A/B
 *          control that distinguishes "hook not running" from "hook running,
 *          maths wrong".
 * BINDTEST the Phase 0 behaviour: scale cot(fovy/2) by a constant. Kept
 *          because it is the cheapest possible proof the hook still binds
 *          after an upstream merge.
 * STEREO   Phase 1 step 1. Rebuild the frustum per eye.                       */
#define GE_VR_MODE_OFF      0
#define GE_VR_MODE_BINDTEST 1
#define GE_VR_MODE_STEREO   2
#define GE_VR_MODE_HOSTEYE  3

/* The A/B against stock was run 2026-08-22 with this set to OFF. Result in
 * docs\14: the blue void band at the screen edge is OURS - it appears only
 * under the wide frustum. Restored to STEREO; the band is now part of gate
 * 3c's acceptance test rather than a loose end. */
#ifndef GE_VR_MODE
#define GE_VR_MODE GE_VR_MODE_HOSTEYE
#endif

/* --- HOSTEYE: the culling frustum, step 3c -------------------------------- *
 *
 * In HOSTEYE this file no longer builds an eye frustum. RT64 does that, per
 * eye, host-side (docs\15). What is left here is the one job only the game can
 * do: make sure the geometry an eye needs was submitted at all.
 *
 * The lever is NOT the projection matrix. Found 2026-08-22 by reading the
 * decomp, after the Perfect Dark PC port - same engine - pointed at the
 * engine's own FOV entry point rather than at matrices:
 *
 *   viSetFovY(fovy)                          fr.c:902
 *     -> g_ViBackData->fovy                  -> guPerspectiveF, fr.c:709
 *                                               ...what gets DRAWN
 *     -> currentPlayerSetPerspective()       -> c_perspfovy
 *     -> currentPlayerSetCameraScale()       -> c_scalex, c_scaley
 *                                            -> c_cameratopnorm,
 *                                               c_cameraleftnorm
 *                                               ...what gets CULLED
 *
 * One variable, g_ViBackData->fovy, feeds both - but only when the change goes
 * through viSetFovY. GE_VR_MODE_STEREO rewrote the matrix AFTER guPerspectiveF
 * had already run, so the drawn frustum widened while c_perspfovy stayed at the
 * stock 60 degrees and the culling frustum stayed narrow. Geometry outside the
 * 60 degree cone was never submitted, which is the unrendered sliver at the
 * screen edge recorded in docs\14.
 *
 * 106 degrees vertical. With the game's aspect that is about 121 degrees
 * horizontal, which contains the headset's 108 degree two-eye union plus
 * roughly the head-turn margin a 30 Hz display list needs. The superset only
 * has to CONTAIN the eye frustums, not match them - too generous merely
 * submits geometry that is then clipped. */
#ifndef GE_VR_CULL_FOVY_DEG
#define GE_VR_CULL_FOVY_DEG 106.0f
#endif

/* lib/ge/src/fr.h:137 FOV_Y_F. Copied rather than included: the patch build
 * puts lib/ge/include on the include path, not lib/ge/src. */
#define GE_VR_STOCK_FOVY_DEG 60.0f

/* Widening is MULTIPLICATIVE, never an assignment. bondview2.c:3069 calls
 * viSetFovY(zoominfovy) for scope zoom; assigning a constant would break it. */
#define GE_VR_CULL_FOVY_SCALE (GE_VR_CULL_FOVY_DEG / GE_VR_STOCK_FOVY_DEG)

/* --- HOSTEYE: znear, clamped DOWN --------------------------------------- *
 *
 * The opposite of what GE_VR_MIN_ZNEAR_UNITS did, and for a reason that only
 * appeared once the frustum got wide (docs\19).
 *
 * The frustum's near FACE is a rectangle of half-width n * tanRight. At the
 * game's per-level znear of up to 30 units and the headset's tanRight of 1.376,
 * that is a 41-unit-wide pane floating in front of the eye - and standing
 * against a wall puts the wall through it. Everything the pane cuts away shows
 * the background fill, because there is nothing behind a wall.
 *
 * Shrinking n shrinks the near face proportionally: at n = 2 the half-width is
 * 2.8 units instead of 41.
 *
 * 2.0 is not a novel value. The game itself ships levels at znear 2, so no part
 * of the engine is being asked to do something it does not already do. And the
 * depth-precision objection does not apply here: RT64 renders to D32_FLOAT
 * (rt64_render_target.cpp:513), not the N64's 16-bit z.
 *
 * Clamping DOWN means the clamp only ever fires on levels whose native znear is
 * larger, and never widens a level that was already tight. */
#ifndef GE_VR_MAX_ZNEAR_UNITS
#define GE_VR_MAX_ZNEAR_UNITS 2.0f
#endif

/* Phase 0 constant. 0.625 takes the game's 60 degree vertical FOV to roughly
 * 85 degrees — unmistakable at a glance, still a navigable world. */
#define GE_BT_COT_SCALE 0.625f

/* The game's per-level znear runs 2..30 game units.
 *
 * This was 10.0f, on the reasoning that clamping up costs no field of view (n
 * does cancel out of the x/y scale) and buys depth precision, with "no visible
 * near clipping: 10 units is well inside the player's own collision radius".
 *
 * BOTH halves of that turned out to be wrong, 2026-08-22:
 *
 * 1. The collision radius stops the PLAYER walking into geometry. It does not
 *    stop a character walking into the player, and it does not apply to props
 *    brushed past on either side. Reported symptom: characters vanish at close
 *    range, and side objects vanish and show the geometry behind them. The
 *    side asymmetry is the signature of a near PLANE - it is perpendicular to
 *    the view axis, so an object off-axis at the same radial distance has a
 *    smaller z and crosses the plane sooner.
 *
 * 2. The depth-precision argument is about the N64's 16-bit z encoding. RT64
 *    does not reproduce it: render targets are D32_FLOAT
 *    (rt64_render_target.cpp:513). There is precision to spare at n = 2.
 *
 * A near plane also has to be SMALL in VR, not large, because the player can
 * lean in and put their face against a wall. The old value pushed in exactly
 * the wrong direction for the thing being built.
 *
 * At 1.0f the clamp never fires - the game's own per-level value always wins -
 * so this is a pass-through. Overridable from the build for A/B testing. */
#ifndef GE_VR_MIN_ZNEAR_UNITS
#define GE_VR_MIN_ZNEAR_UNITS 1.0f
#endif

#define GE_VR_EYE_LEFT  0
#define GE_VR_EYE_RIGHT 1

/* A true eye frustum is close to square. Shown full-screen on a 16:9 monitor
 * it looks horizontally stretched — which is correct, not a bug, but it makes
 * eyeballing the asymmetry harder. With this set, the horizontal tangents are
 * scaled about zero to match the aspect ratio the game was already rendering
 * at, so the preview stays undistorted. Scaling about zero rather than about
 * the frustum centre leaves the skew terms untouched, so the off-centre-ness
 * being tested survives the fit. Set to 0 to see the raw eye frustum. */
#ifndef GE_VR_PREVIEW_FIT_ASPECT
#define GE_VR_PREVIEW_FIT_ASPECT 1
#endif

/* --- eye parameters ------------------------------------------------------- */

typedef struct GeVrEyeParams {
    f32 tanLeft;  /* negative */
    f32 tanRight; /* positive */
    f32 tanUp;    /* positive */
    f32 tanDown;  /* negative */
} GeVrEyeParams;

/* Which eye this frame renders. Non-const on purpose: it is the knob to flip
 * from a debugger to confirm the two eyes differ, and later the thing the
 * two-target submission loop writes between passes. */
s32 g_geVrEye = GE_VR_EYE_LEFT;

/* MEASURED, not guessed — from ge-vr-xrprobe against the rig's actual headset
 * (Pimax via SteamVR/OpenXR 2.16.7, system "aapvr", IPD 63.5 mm, 90 Hz):
 *
 *   per eye  outer 53.99 deg, inner 46.01, up 45.50, down 45.50
 *            = 100.0 deg horizontal, 91.0 deg vertical
 *   cant     0.000 deg — the panels are PARALLEL, so per-eye projection plus an
 *            IPD offset is sufficient and no per-eye view rotation is needed.
 *
 * The earlier values here were plausible Quest 3 numbers and were wrong for this
 * rig in a way that mattered: they guessed 53/52 deg vertical against an actual
 * 45.5, i.e. a 105 deg vertical FOV where the headset wants 91. That renders a
 * world noticeably too small and too far away, which is the kind of error that
 * gets blamed on world scale rather than on the frustum.
 *
 * These are still THIS headset at THIS IPD setting. They are a better stand-in,
 * not a substitute for querying the runtime — see geVrGetEyeParams() below.
 *
 * The inward asymmetry (outer 54 vs inner 46) is what makes this a stereo
 * frustum rather than merely a wide one, and it is what to look for on the
 * monitor: the centre of projection sits off to one side, and jumps the other
 * way when g_geVrEye flips. */
GeVrEyeParams g_geVrEyeParams[2] = {
    /* LEFT  */ { -1.3760f, 1.0358f, 1.0176f, -1.0176f },
    /* RIGHT */ { -1.0358f, 1.3760f, 1.0176f, -1.0176f },
};

/* THE SEAM. Everything above is a stand-in for the OpenXR runtime. When Phase 2
 * lands, this becomes a host import declared in patches.h and given an address
 * in patches/syms.ld (next free slot is 0x8F000114; the pointer-out-arg pattern
 * to copy is recomp_get_gyro_deltas in src/game/recomp_api.cpp), and the host
 * fills the struct from xrLocateViews' XrFovf via tanf. Nothing else in this
 * file should need to change when that happens. */
#if GE_VR_MODE == GE_VR_MODE_STEREO
static const GeVrEyeParams* geVrGetEyeParams(void) {
    return &g_geVrEyeParams[(g_geVrEye == GE_VR_EYE_RIGHT) ? 1 : 0];
}
#endif

/* --- counters ------------------------------------------------------------- *
 * Observable from a debugger, or printed from an existing patch.
 *   set calls both zero      -> the patch never ran. Attachment problem, not a
 *                              plan problem: check patches.elf contains it.
 *   set calls nonzero, image unchanged
 *                            -> the setters run but the world projection
 *                               reaches the RSP by another path. This is the
 *                               only result that should stop the project.
 *   bailouts climbing        -> geVrBuildProj is rejecting the incoming matrix.
 *                               Something upstream of us is not a guPerspectiveF
 *                               product. Read the four recovered values. */
u32 g_geBtSetMtxCalls  = 0;
u32 g_geBtSetMtxfCalls = 0;
u32 g_geVrProjRebuilds = 0;
u32 g_geVrProjBailouts = 0;

/* HOSTEYE. If this stays at zero the viSetFovY patch never ran, and the first
 * suspect is symbol resolution for the two functions it calls rather than
 * anything about the maths. */
u32 g_geVrFovWidenCalls = 0;

#if GE_VR_MODE == GE_VR_MODE_BINDTEST || GE_VR_MODE == GE_VR_MODE_STEREO

/* --- fixed-point element access ------------------------------------------- *
 * Mtx is sixteen s15.16 values: eight words of integer halves followed by eight
 * of fractional halves (PR/gbi.h). Element (r,c) lives in word k = r*2 + c/2;
 * even columns take the high halves, odd columns the low. Written from that
 * documented layout, not from libultra's mtxutil.c, which carries SGI's
 * proprietary notice (VENDORING.md section 1 rule 3). */

static f32 geVrGetFixed(const Mtx* m, s32 r, s32 c) {
    s32 k = r * 2 + (c >> 1);
    const u32* iw = (const u32*) &m->m[k >> 2][k & 3];
    const u32* fw = (const u32*) &m->m[(k + 8) >> 2][(k + 8) & 3];
    s32 fixed;

    if ((c & 1) == 0) fixed = (s32) ((*iw & 0xffff0000u) | ((*fw >> 16) & 0xffffu));
    else              fixed = (s32) (((*iw & 0xffffu) << 16) | (*fw & 0xffffu));

    return (f32) fixed / 65536.0f;
}

static void geVrSetFixed(Mtx* m, s32 r, s32 c, f32 value) {
    s32 k = r * 2 + (c >> 1);
    u32* iw = (u32*) &m->m[k >> 2][k & 3];
    u32* fw = (u32*) &m->m[(k + 8) >> 2][(k + 8) & 3];
    s32 fixed = (s32) (value * 65536.0f);

    if ((c & 1) == 0) {
        *iw = (*iw & 0x0000ffffu) | ((u32) fixed & 0xffff0000u);
        *fw = (*fw & 0x0000ffffu) | (((u32) fixed << 16) & 0xffff0000u);
    } else {
        *iw = (*iw & 0xffff0000u) | (((u32) fixed >> 16) & 0xffffu);
        *fw = (*fw & 0xffff0000u) | ((u32) fixed & 0xffffu);
    }
}

#endif /* GE_VR_MODE != GE_VR_MODE_OFF */

#if GE_VR_MODE == GE_VR_MODE_STEREO

/* --- the projection itself ------------------------------------------------ */

typedef struct GeVrProj {
    f32 sx; /* -> [0][0] */
    f32 sy; /* -> [1][1] */
    f32 ox; /* -> [2][0] */
    f32 oy; /* -> [2][1] */
    f32 za; /* -> [2][2], only if zValid */
    f32 zb; /* -> [3][2], only if zValid */
    s32 zValid;
} GeVrProj;

static s32 geVrNonZero(f32 v) { return v < -0.0001f || v > 0.0001f; }

/* srcXX/srcYY/srcA/srcB are [0][0], [1][1], [2][2] and [3][2] as the game left
 * them. We need them for two things and two things only: the aspect ratio the
 * game was rendering at, and the per-level near and far planes.
 *
 * Recovering n and f: guPerspectiveF writes A = (n+f)/(n-f) and B = 2nf/(n-f).
 * Then A-1 = 2f/(n-f) so B/(A-1) = n, and A+1 = 2n/(n-f) so B/(A+1) = f. No
 * approximation, no trig, two divides.
 *
 * Returns 0 and touches nothing if the incoming matrix does not look like a
 * guPerspectiveF product. A caller that bails leaves the game's own matrix in
 * place, which renders the flat image — the correct failure, since a wrong
 * frustum in a headset is a nausea event and a flat frame is merely wrong. */
static s32 geVrBuildProj(f32 srcXX, f32 srcYY, f32 srcA, f32 srcB, GeVrProj* out) {
    const GeVrEyeParams* e = geVrGetEyeParams();
    f32 tl = e->tanLeft, tr = e->tanRight, tu = e->tanUp, td = e->tanDown;
    f32 w = tr - tl;
    f32 h = tu - td;
    f32 n, f, den;

    if (w <= 0.0f || h <= 0.0f) return 0;
    if (!geVrNonZero(srcXX) || !geVrNonZero(srcYY)) return 0;

#if GE_VR_PREVIEW_FIT_ASPECT
    {
        /* guPerspectiveF put cot/aspect at [0][0] and cot at [1][1], so the
         * aspect the game chose is simply [1][1] / [0][0]. */
        f32 aspect = srcYY / srcXX;
        f32 k = (h * aspect) / w;
        tl *= k;
        tr *= k;
        w  *= k;
    }
#endif

    out->sx = 2.0f / w;
    out->sy = 2.0f / h;
    out->ox = (tr + tl) / w;
    out->oy = (tu + td) / h;

    out->zValid = 0;
    out->za = srcA;
    out->zb = srcB;

    den = srcA - 1.0f;
    if (geVrNonZero(den)) {
        n = srcB / den;
        den = srcA + 1.0f;
        if (geVrNonZero(den)) {
            f = srcB / den;
            if (n < GE_VR_MIN_ZNEAR_UNITS) n = GE_VR_MIN_ZNEAR_UNITS;
            /* f must stay comfortably beyond n or the z row goes singular. */
            if (f > n + 1.0f) {
                den = n - f;
                out->za = (n + f) / den;
                out->zb = 2.0f * n * f / den;
                out->zValid = 1;
            }
        }
    }
    return 1;
}

#endif /* GE_VR_MODE == GE_VR_MODE_STEREO */

/* --- gating --------------------------------------------------------------- *
 * Menus and the title screen share viSetupCurrentPlayerView with the world, so
 * touching the projection unconditionally distorts the front end — at Phase 0's
 * 0.3 the file-select options were covered by an overlay stretched past its
 * scissor box. Gate on stage instead. LEVELID_NONE (-1) is "no level loaded";
 * LEVELID_TITLE (90) is the front end. Everything else is a playable level.
 *
 * This does NOT cover the in-level pause menu / watch, which run with a level
 * loaded. Phase 3 re-renders those as world-space panels anyway, so gating them
 * out now would be work thrown away. */
static s32 geVrInLevel(void) {
    return g_StageNum != LEVELID_NONE && g_StageNum != LEVELID_TITLE;
}

/* geVrInLevel() alone is NOT a sufficient gate, established the hard way
 * 2026-08-22 (docs\20). "A level is loaded" is true during a great deal that is
 * not gameplay: the intro walk, death cams, the swirl transitions, the briefing
 * and mission-complete menus, and demo playback on the title screen. Widening
 * the FOV during those stretches overlays past their scissor boxes - the exact
 * black-border-over-the-menu failure Phase 0 hit at cot scale 0.3 - and puts
 * Bond off-centre in the intro.
 *
 * The robust form gates IN the two cameras that are gameplay rather than gating
 * OUT a list of exceptions, because the exception list is open-ended and the
 * inclusion list is not:
 *
 *   CAMERAMODE_FP   first person, singleplayer
 *   CAMERAMODE_MP   multiplayer
 *
 * Everything else - NONE, INTRO, FADESWIRL, SWIRL, DEATH_CAM_SP, DEATH_CAM_MP,
 * POSEND, FP_NOINPUT, FADE_TO_TITLE - renders stock.
 *
 * FP_NOINPUT is deliberately excluded. It covers first-person moments where the
 * player has no control, which is where in-level menus sit. The cost is an FOV
 * change when one opens; the alternative is the overlay bug, and Phase 3
 * replaces those screens with world-space panels anyway.
 *
 * demoMode is the title-screen attract loop. widescreen.c special-cases it for
 * the same reason at bg.c's screen bounds; this is the same exclusion. */
extern int demoMode;

static s32 geVrWorldCamera(void) {
    return geVrInLevel()
        && demoMode == 0
        && (g_CameraMode == CAMERAMODE_FP || g_CameraMode == CAMERAMODE_MP);
}

/* --- HOSTEYE: the culling frustum ------------------------------------------ *
 *
 * viSetFovY is called EVERY FRAME - lvlRender re-sets it, and front.c calls it
 * from eight places - so setting the FOV once somewhere else would be
 * overwritten immediately. Patching the setter is not merely convenient, it is
 * the only stable place to put this.
 *
 * The body below is the original three statements from fr.c:902-907 with one
 * line added. Replacing it wholesale loses no behaviour.
 *
 * These two are game functions not declared in patches/externs.h, so they are
 * declared here. If 3c builds but the FOV never widens - or it crashes on the
 * first frame - suspect these symbols before suspecting the arithmetic. */
#if GE_VR_MODE == GE_VR_MODE_HOSTEYE

extern void currentPlayerSetPerspective(f32 near, f32 fovy, f32 aspect);
extern void currentPlayerSetCameraScale(void);

/* Trace, 2026-08-22. The gate below changed nothing observable, and the two
 * possible reasons need opposite fixes:
 *
 *   gameplay still wide, menus still wrong -> g_CameraMode is not
 *       discriminating; it reads FP during menus too, or camera_mode is the
 *       live one and g_CameraMode is not.
 *   everything now stock -> the gate is always false, and the first suspect is
 *       g_CameraMode failing to resolve as a patch-space symbol. The link uses
 *       --unresolved-symbols=ignore-all, so an unresolved read is silent and
 *       plausibly returns 0, which is CAMERAMODE_NONE.
 *
 * Printing both camera globals settles it in one run. Set GE_VR_TRACE_FOV to 0
 * to silence. */
/* Answered 2026-08-22 (docs\21): the cause was the HOST frustum override, left
 * enabled by a stale GE_VR_FRUSTUM in a reused shell. Off by default now; build
 * with -DGE_VR_TRACE_FOV=1 to bring it back. */
#ifndef GE_VR_TRACE_FOV
#define GE_VR_TRACE_FOV 0
#endif

RECOMP_PATCH void viSetFovY(f32 fovy) {
    g_geVrFovWidenCalls++;

#if GE_VR_TRACE_FOV
    {
        static u32 traceTick = 0;
        if ((traceTick++ % 60) == 0) {
            recomp_printf("[gevr] stage=%d demo=%d g_CameraMode=%d camera_mode=%d inLevel=%d worldCam=%d fovyIn=%d znear=%d\n",
                (s32) g_StageNum, (s32) demoMode, (s32) g_CameraMode, (s32) camera_mode,
                (s32) geVrInLevel(), (s32) geVrWorldCamera(),
                (s32) fovy, (s32) g_ViBackData->znear);
        }
    }
#endif

    /* Tell the host what gate we are applying, so its per-eye frustum follows
     * the same rule. Called unconditionally and every frame - the host needs
     * the FALSE just as much as the TRUE, since false is what keeps the eye
     * frustum off the Nintendo logo and the intro walk (docs\21). */
    recomp_ge_vr_set_world_camera(geVrWorldCamera());

    if (geVrWorldCamera()) {
        fovy *= GE_VR_CULL_FOVY_SCALE;

        /* A vertical FOV at or past 180 makes the projection singular and the
         * frustum normals meaningless. Nothing should reach this with a scale
         * of 1.77, but zoom multiplies too and a scope at 3x would. */
        if (fovy > 170.0f) {
            fovy = 170.0f;
        }
    }

    /* Mutating g_ViBackData->znear is what reaches guPerspectiveF at fr.c:709 -
     * it reads the field directly, so clamping only the value passed to
     * currentPlayerSetPerspective would fix culling and not drawing.
     *
     * The write persists, but viSetFovY runs every frame and the front end
     * calls it too, so the value is re-derived continuously and a level load
     * that resets znear is picked up on the next frame. */
    if (geVrWorldCamera() && (g_ViBackData->znear > GE_VR_MAX_ZNEAR_UNITS)) {
        g_ViBackData->znear = GE_VR_MAX_ZNEAR_UNITS;
    }

    g_ViBackData->fovy = fovy;
    currentPlayerSetPerspective(g_ViBackData->znear, g_ViBackData->fovy, g_ViBackData->aspect);
    currentPlayerSetCameraScale();
}

/* --- and the getter, which is NOT optional -------------------------------- *
 *
 * The game reads its own FOV back and compares it against the stock constant:
 *
 *   bondview.c:2631   fovy = viGetFovY();
 *                     if (fovy == 0 || fovy == 60.0f) fovy = 1;
 *                     else fovy = ADJUST_ZOOM_FOV(60.0f) / fovy;
 *
 * With 106 sitting in g_ViBackData->fovy that equality never holds, so the game
 * believes it is permanently zoomed at about 0.57x. Reported from play as scope
 * zoom working, then failing, then appearing on a weapon that has no scope.
 * propobj.c:932 reads it too.
 *
 * docs\18 required the widening to be MULTIPLICATIVE so zoom would survive, and
 * got the arithmetic right while missing that the value is also read back and
 * compared. Dividing it out here keeps the game's own view of its FOV exactly
 * as it was, while drawing and culling keep the wide value.
 *
 * Safe in a getter, despite the warning at the top of this file. That warning
 * is about MUTATING state in a getter, which compounds across the many calls
 * per frame; this only divides the value it returns and stores nothing.
 * viSetFovY(viGetFovY()) therefore round-trips exactly.
 *
 * The gate has to match the setter's, or the two disagree at camera-mode
 * boundaries and the game sees a step change in its own FOV. */
RECOMP_PATCH f32 viGetFovY(void) {
    if (geVrWorldCamera()) {
        return g_ViBackData->fovy / GE_VR_CULL_FOVY_SCALE;
    }

    return g_ViBackData->fovy;
}

#endif /* GE_VR_MODE == GE_VR_MODE_HOSTEYE */

/* --- the patched setters -------------------------------------------------- *
 * Two matrices, one projection. The fixed-point Mtx is what the RSP transforms
 * vertices with; the float Mtxf is what the CPU culls and picks with. They must
 * agree, or geometry is culled against a frustum it is not drawn in — which
 * shows up as things popping at the edge of vision, the single most nauseating
 * failure mode available in a headset. Both paths below run the same builder on
 * the same recovered inputs for exactly that reason. */

RECOMP_PATCH void currentPlayerSetProjectionMatrix(Mtx* matrix) {
    g_geBtSetMtxCalls++;

#if GE_VR_MODE == GE_VR_MODE_BINDTEST
    if (matrix && geVrInLevel()) {
        geVrSetFixed(matrix, 0, 0, geVrGetFixed(matrix, 0, 0) * GE_BT_COT_SCALE);
        geVrSetFixed(matrix, 1, 1, geVrGetFixed(matrix, 1, 1) * GE_BT_COT_SCALE);
    }
#elif GE_VR_MODE == GE_VR_MODE_STEREO
    if (matrix && geVrInLevel()) {
        GeVrProj p;
        if (geVrBuildProj(geVrGetFixed(matrix, 0, 0), geVrGetFixed(matrix, 1, 1),
                          geVrGetFixed(matrix, 2, 2), geVrGetFixed(matrix, 3, 2), &p)) {
            geVrSetFixed(matrix, 0, 0, p.sx);
            geVrSetFixed(matrix, 1, 1, p.sy);
            geVrSetFixed(matrix, 2, 0, p.ox);
            geVrSetFixed(matrix, 2, 1, p.oy);
            if (p.zValid) {
                geVrSetFixed(matrix, 2, 2, p.za);
                geVrSetFixed(matrix, 3, 2, p.zb);
            }
            g_geVrProjRebuilds++;
        } else {
            g_geVrProjBailouts++;
        }
    }
#endif

    g_CurrentPlayer->projmatrix = matrix;
}

RECOMP_PATCH void currentPlayerSetProjectionMatrixF(Mtxf* matrix) {
    g_geBtSetMtxfCalls++;

#if GE_VR_MODE == GE_VR_MODE_BINDTEST
    if (matrix && geVrInLevel()) {
        matrix->m[0][0] *= GE_BT_COT_SCALE;
        matrix->m[1][1] *= GE_BT_COT_SCALE;
    }
#elif GE_VR_MODE == GE_VR_MODE_STEREO
    if (matrix && geVrInLevel()) {
        GeVrProj p;
        if (geVrBuildProj(matrix->m[0][0], matrix->m[1][1],
                          matrix->m[2][2], matrix->m[3][2], &p)) {
            matrix->m[0][0] = p.sx;
            matrix->m[1][1] = p.sy;
            matrix->m[2][0] = p.ox;
            matrix->m[2][1] = p.oy;
            if (p.zValid) {
                matrix->m[2][2] = p.za;
                matrix->m[3][2] = p.zb;
            }
        }
        /* Counters are incremented on the fixed-point path only. Both setters
         * are called once each per frame from the same site, so counting twice
         * would just double every number and make the ratio meaningless. */
    }
#endif

    g_CurrentPlayer->projmatrixf = matrix;
}

/* ---------------------------------------------------------------------------
 * WHAT TO EXPECT ON THE MONITOR, AND WHAT EACH WRONG PICTURE MEANS
 * ---------------------------------------------------------------------------
 * Correct: a slightly wider view than stock, with the centre of projection
 * pushed off to one side. Flip g_geVrEye and the centre moves the other way by
 * the same amount. Nothing shears, nothing swims, straight edges stay straight.
 *
 * Sheared world, verticals leaning   -> the skew terms went into column 2
 *                                       instead of row 2. Transpose them.
 * Correct shape, geometry popping at
 * the screen edge                    -> the two setters disagree. The CPU is
 *                                       culling against one frustum and the RSP
 *                                       drawing with another; check the Mtxf
 *                                       path took the same branch as the Mtx one.
 * Black frame                        -> the z row went singular. zValid should
 *                                       have caught it; read n and f.
 * Stock image, counters climbing     -> geVrBuildProj bailed. Watch
 *                                       g_geVrProjBailouts.
 * Stretched but otherwise right      -> expected with GE_VR_PREVIEW_FIT_ASPECT
 *                                       set to 0. Not a bug.
 *
 * The vocabulary from the interpolation work still applies to anything moving:
 * swimming means RT64 matched the wrong pair, ghosting means it inherited an id
 * it does not own, flicker means it could not pair at all. Those are matrix-group
 * problems, not projection problems, and nothing in this file should cause them.
 */
