/*
 * interpolation.c — RT64 matrix-group tagging.
 *
 * ---------------------------------------------------------------------------
 * WHY GEOMETRY SWIMS ABOVE THE NATIVE FRAMERATE
 * ---------------------------------------------------------------------------
 * RT64 interpolates between the game's 30/25 Hz frames. To do that it has to
 * know which matrix in this frame corresponds to which matrix in the last one.
 * A port tells it by tagging matrices with a stable id.
 *
 * When nothing is tagged, TransformGroup::matrixId defaults to G_EX_ID_AUTO
 * (rt64_transform_group.h:13), which makes RT64 fall back to content matching:
 * GameFrame::hashFromCall (rt64_game_frame.cpp:740) pairs draw calls between
 * frames on a hash of colour combiner, other mode, geometry mode and TRIANGLE
 * COUNT. In GoldenEye a great many draw calls agree on all four, so the hash
 * collides between unrelated objects and RT64 lerps one object's transform
 * toward a different object's.
 *
 * Room matrices make this especially violent. setupRoomTransformationMatrix
 * builds each one relative to the player:
 *
 *     m[3][n] = room_pos[n] * scale - g_CurrentPlayer->current_model_pos[n]
 *
 * so every room matrix changes every frame as you move, and a mismatch lerps
 * between two rooms metres apart. Hence "assets move all over the place as you
 * move" — and hence why it is worst when moving and near-invisible when still.
 *
 * ---------------------------------------------------------------------------
 * THE FIX
 * ---------------------------------------------------------------------------
 * roomID is a genuinely stable identity: the same room is the same room next
 * frame, whatever slot setupRoomTransformationMatrix hands it in the shared
 * roomMatrices pool. Tagging with it takes RT64 off the guessing path entirely
 * (G_EX_ORDER_LINEAR + a real id skips content matching — rt64_game_frame.cpp
 * :713-714) and onto exact frame-to-frame identity.
 *
 * SkipRot because rooms never rotate; position, scale and skew interpolate.
 *
 * ids are roomID + 1 because 0 is G_EX_ID_IGNORE (meaning "never interpolate")
 * and 0xFFFFFFFF is G_EX_ID_AUTO. Room ids are small, so there is no risk of
 * colliding with either.
 *
 * This covers all eight call sites of applyRoomMatrixToDisplayList: level room
 * geometry (bg.c x2), explosions, smoke, scorch marks, bullet impacts and
 * glass. Characters and props are NOT covered — they emit their matrices
 * elsewhere and need their own ids. See claude/interpolation-plan.md.
 *
 * NOTE ON DISPLAY LIST BUDGET: each tag costs TWO Gfx slots, not one.
 * G_EX_COMMAND2 writes at _cmd+0 and _cmd+1, and evaluates its cmd argument
 * twice on purpose (that is what the bare `(void)(cmd);` line is for), so the
 * `gdl++` idiom advances by two. GoldenEye's display list buffers are fixed
 * size; if the master list overflows the symptom is dropped or corrupted
 * geometry. Watch for it on high room/prop counts (Surface, Streets) before
 * assuming the tagging itself is wrong.
 */
#include "patches.h"

extern Mtx roomMatrices[300];
s32 setupRoomTransformationMatrix(s32 room);

/* Set to 0 to build the tag out again without touching anything else. */
#ifndef GE_INTERP_ROOMS
#define GE_INTERP_ROOMS 1
#endif

/* --- id namespaces ------------------------------------------------------- *
 * applyRoomMatrixToDisplayList is the shared entry point for EIGHT different
 * kinds of geometry (room walls, explosions, smoke, scorch marks, bullet
 * impacts, glass), and it tags all of them with the same roomID + 1. That was
 * right for slice 1, where the point was to stop rooms lerping into each other,
 * and it is wrong once you care about what is drawn INSIDE a room: the room's
 * own walls, its scorch marks and its bullet holes all claim one identity, and
 * RT64 pairs across them.
 *
 * The cheap correction is a namespace: a caller sets a bias before calling in,
 * and clears it after. Room walls keep the bare roomID + 1, so slice 1's
 * behaviour is bit-for-bit unchanged and nothing that currently works can
 * regress. Anything that opts in gets its own band of the id space.
 *
 * Bands are 0x10000 apart and room ids are small, so no band can reach the
 * next. 0 stays free (G_EX_ID_IGNORE) and nothing comes near 0xFFFFFFFF
 * (G_EX_ID_AUTO).
 *
 * The render path is single-threaded, so a plain global is sufficient. Every
 * setter MUST clear it on the way out — a leaked bias silently moves room walls
 * into someone else's band and looks like slice 1 regressing. */
#define GE_IDBAND_ROOM          0x00000000
#define GE_IDBAND_BULLET_IMPACT 0x00010000

s32 g_geRoomIdBias = GE_IDBAND_ROOM;

RECOMP_PATCH Gfx* applyRoomMatrixToDisplayList(Gfx* gdl, int roomID) {
    s32 roomIndex;

    roomIndex = setupRoomTransformationMatrix(roomID);

#if GE_INTERP_ROOMS
    gEXMatrixGroupDecomposedSkipRot(gdl++, (u32) (roomID + 1 + g_geRoomIdBias), G_EX_NOPUSH, 0,
                                    G_EX_EDIT_NONE);
#endif

    gSPMatrix(gdl++, &roomMatrices[roomIndex], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    return gdl;
}

/* =========================================================================
 * SLICE 2 — characters, objects, weapons, doors, explosions, smoke
 * =========================================================================
 * Two problems, one fix.
 *
 * 1. Props were never tagged, so they sat on RT64's content-matching path and
 *    got paired with whatever draw call happened to hash the same.
 *
 * 2. Worse, after slice 1 they INHERITED the room's id. gEXMatrixGroup with
 *    G_EX_NOPUSH replaces the current group and it persists until the next
 *    group command, and bg.c's render order is:
 *
 *        set projection; chrpropsRenderPass(room, 0)   <- props
 *        set projection; bgRenderRoomPrimary(room)     <- tags id = room+1
 *        set projection; chrpropsRenderPass(room, 2)   <- props, still room+1
 *
 *    so every prop drawn after a room's geometry claimed that room's identity.
 *    Many different props sharing one id across frames is exactly the input
 *    that makes RT64 interpolate one object toward another — the moving ghost
 *    copy you can walk through, while the correctly-tagged room geometry stays
 *    put.
 *
 * chrpropRender is the single dispatch every prop type passes through
 * (chrprop.c:427), and PropRecord* is a stable identity across frames — the
 * same guard is the same pointer next frame. Tagging here fixes both problems
 * at one site.
 *
 * No closing tag is emitted. Every consumer downstream re-tags before it draws
 * (the next prop here, room geometry via applyRoomMatrixToDisplayList), so the
 * scope closes itself, and skipping the close halves the display list cost —
 * which matters, because each tag is two Gfx slots (see the note above).
 *
 * VERTEX INTERPOLATION IS NOT OPTIONAL HERE. GoldenEye skins characters on the
 * CPU: modelRenderNodeDl (model.c:4249) uploads already-transformed vertices
 * with gSPSegment(SPSEGMENT_MODEL_VTX, rwdata->...Vertices) and emits no
 * per-bone gSPMatrix at all. So a group whose vert component is SKIP gets a
 * smoothly interpolated TRANSFORM wrapped around vertices that still step at
 * 30 Hz. The two disagree, and the disagreement is largest exactly when the
 * animation is fastest — a character being shot, a gun recoiling. That is the
 * first version of this patch's bug, and gEXMatrixGroupDecomposedVerts (vert =
 * G_EX_COMPONENT_INTERPOLATE) is the fix. It is harmless for rigid props: if
 * the vertices are identical between frames the lerp is the identity.
 *
 * ...AND THE TRANSFORM COMPONENTS ARE ACTIVELY HARMFUL FOR CHARACTERS.
 * chrRenderProp (chr.c:2871) emits no gSPMatrix whatsoever — it fills a
 * ModelRenderData and the model pipeline writes world-space vertices. So a
 * character's group has no matrix of its own, and pos/rot/scale/skew/persp
 * refer to whatever matrix was last loaded, which several props share while
 * each claims a distinct id. Asking RT64 to interpolate those is asking it to
 * track an identity that isn't there. Characters therefore get SKIP on every
 * transform component and INTERPOLATE on vert and tile only.
 *
 * Rigid props keep the full DecomposedVerts tag: empirically stable, and the
 * extra components cost nothing when the geometry doesn't deform.
 */

/* PROP_TYPE, from lib/ge/src/bondconstants.h:3802. Not in patches/structs.h. */
#define GE_PROP_TYPE_OBJ        1
#define GE_PROP_TYPE_DOOR       2
#define GE_PROP_TYPE_CHR        3
#define GE_PROP_TYPE_WEAPON     4
#define GE_PROP_TYPE_VIEWER     6
#define GE_PROP_TYPE_EXPLOSION  7
#define GE_PROP_TYPE_SMOKE      8

Gfx* chrRenderProp(PropRecord* prop, Gfx* gdl, s32 withalpha);
Gfx* chrobjRenderProp(PropRecord* prop, Gfx* gdl, s32 withalpha);
Gfx* explosionRenderPropExplosion(PropRecord* prop, Gfx* gdl, s32 withalpha);
Gfx* explosionRenderPropSmoke(PropRecord* prop, Gfx* gdl, s32 withalpha);
Gfx* bondviewRenderProp(PropRecord* prop, Gfx* gdl, s32 withalpha);

#ifndef GE_INTERP_PROPS
#define GE_INTERP_PROPS 1
#endif

/* Props live in a fixed pool in RDRAM (0x80xxxxxx), so the pointer is stable
 * and unique for as long as the prop exists. Shifting off the two alignment
 * bits and forcing the top bit keeps the result far away from the room ids
 * (small, 1..~300) and from both reserved values. */
static u32 geInterpPropId(PropRecord* prop, s32 withalpha) {
    u32 id = (((u32) prop) >> 2) | 0x40000000u;
    /* One prop can be drawn more than once in a frame (chrpropsRenderPass runs
     * passes 0/1/2, and the alpha and opaque halves are separate calls). Two
     * draws claiming one identity is the same mismatch we are trying to remove,
     * so fold the pass distinction into the id. */
    if (withalpha) {
        id |= 0x20000000u;
    }
    if (id == G_EX_ID_IGNORE || id == G_EX_ID_AUTO) {
        id = 0x40000001u;
    }
    return id;
}

RECOMP_PATCH Gfx* chrpropRender(Gfx* gdl, PropRecord* prop, s32 withalpha) {
    u8 type = prop->type;

#if GE_INTERP_PROPS
    if (type == GE_PROP_TYPE_CHR) {
        /* Skeletal, and matrix-less: vertices are the ONLY thing to interpolate. */
        gEXMatrixGroupDecomposed(gdl++, geInterpPropId(prop, withalpha), G_EX_NOPUSH, 0,
                                 G_EX_COMPONENT_SKIP,        /* pos   */
                                 G_EX_COMPONENT_SKIP,        /* rot   */
                                 G_EX_COMPONENT_SKIP,        /* scale */
                                 G_EX_COMPONENT_SKIP,        /* skew  */
                                 G_EX_COMPONENT_SKIP,        /* persp */
                                 G_EX_COMPONENT_INTERPOLATE, /* vert  */
                                 G_EX_COMPONENT_INTERPOLATE, /* tile  */
                                 G_EX_ORDER_LINEAR, G_EX_EDIT_NONE);
    } else {
        gEXMatrixGroupDecomposedVerts(gdl++, geInterpPropId(prop, withalpha), G_EX_NOPUSH, 0, G_EX_EDIT_NONE);
    }
#endif

    if (type == GE_PROP_TYPE_CHR) {
        gdl = chrRenderProp(prop, gdl, withalpha);
    } else if ((type == GE_PROP_TYPE_OBJ) || (type == GE_PROP_TYPE_WEAPON) || (type == GE_PROP_TYPE_DOOR)) {
        gdl = chrobjRenderProp(prop, gdl, withalpha);
    } else if (type == GE_PROP_TYPE_EXPLOSION) {
        gdl = explosionRenderPropExplosion(prop, gdl, withalpha);
    } else if (type == GE_PROP_TYPE_SMOKE) {
        gdl = explosionRenderPropSmoke(prop, gdl, withalpha);
    } else if (type == GE_PROP_TYPE_VIEWER) {
        gdl = bondviewRenderProp(prop, gdl, withalpha);
    }

#if GE_INTERP_PROPS
    /* Close the group on the way out. Everything drawn after the last prop and
     * before the next tagged thing — muzzle flashes, tracers, bullet effects,
     * the first-person weapon, HUD — would otherwise inherit this prop's id and
     * be interpolated against geometry it has nothing to do with. Short-lived
     * effects are the worst case: a flash that exists for one or two frames has
     * no previous-frame partner at all, so RT64 drops it on the in-between
     * frames, which reads as flicker rather than ghosting.
     *
     * G_EX_ID_IGNORE means "render as-is, do not interpolate", so untagged
     * geometry falls back to honest 30 Hz instead of guessing. This is the same
     * effect as flipping RT64's TransformGroup default from G_EX_ID_AUTO to
     * G_EX_ID_IGNORE, but scoped to the display list rather than the renderer —
     * so it cannot disturb the view/projection group that keeps the camera
     * smooth (rt64_game_frame.cpp:458-468 treats proj groups separately, and a
     * global default flip WOULD have hit it).
     *
     * This is the only site where closing is possible: chrpropRender contains
     * its own draw, whereas applyRoomMatrixToDisplayList returns before its
     * caller emits the room geometry.
     *
     * Cost: two more Gfx slots per prop, four in total. Watch for display list
     * overflow on prop-heavy levels. */
    gEXMatrixGroupNoInterpolation(gdl++, G_EX_NOPUSH, 0, G_EX_EDIT_NONE);
#endif

    return gdl;
}

/* =========================================================================
 * SLICE 3 — the in-game health / armour gauges
 * =========================================================================
 * bondviewRenderGaugeBars draws the health and armour bars that pop up when
 * you take damage. Its geometry is REBUILT every frame by buildGaugeBarDL from
 * hudMakeDamageSegments' output, so the vertex data legitimately differs frame
 * to frame — and being untagged, it sits on RT64's content-matching path where
 * that is exactly the input most likely to mismatch. It also inherits whatever
 * group was last set, which after slice 2 is some arbitrary prop's id.
 *
 * A HUD element in a fixed ortho projection should not be interpolated at all,
 * so the correct tag is gEXMatrixGroupNoInterpolation, which needs no id
 * (G_EX_ID_IGNORE routes it to RT64's ignore list, rt64_game_frame.cpp:733).
 *
 * The body below is the decomp (bondview2.c:8560) copied verbatim; the only
 * change is the tag. Nothing here is behaviour we want to alter.
 */
extern f32 D_800364CC;

Gfx* buildGaugeBarDL(Gfx* gdl, uintptr_t vtxaddr, s32 numvertices);
void hudMakeDamageSegments(struct damage_display_val* arg0, s32 arg1, s32 arg2, f32 arg3);
void matrix_4x4_set_lookat_target(Mtxf* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5,
                                  f32 arg6, f32 arg7, f32 arg8, f32 arg9);
void guOrtho(Mtx* m, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, f32 scale);
Mtx* currentPlayerGetProjectionMatrix(void);

#ifndef GE_INTERP_HUD
#define GE_INTERP_HUD 1
#endif

RECOMP_PATCH Gfx* bondviewRenderGaugeBars(Gfx* gdl) {
    Mtx* lookatmtx;
    Mtx* orthomtx;
    Mtxf lookatmtxf;

#if GE_INTERP_HUD
    gEXMatrixGroupNoInterpolation(gdl++, G_EX_NOPUSH, 0, G_EX_EDIT_NONE);
#endif

    hudMakeDamageSegments(&g_CurrentPlayer->armor_display_values[0].items[0], 0x2e, 1,
                          g_CurrentPlayer->apparentarmour);
    buildGaugeBarDL((Gfx*) &g_CurrentPlayer->watch_body_armor_bar_gdl,
                    (uintptr_t) OS_PHYSICAL_TO_K0(&g_CurrentPlayer->armor_display_values[0].items[0]), 0x2e);

    hudMakeDamageSegments(&g_CurrentPlayer->health_display_values[0].items[0], 0x2e, -1,
                          g_CurrentPlayer->apparenthealth);
    buildGaugeBarDL((Gfx*) &g_CurrentPlayer->watch_health_bar_gdl,
                    (uintptr_t) OS_PHYSICAL_TO_K0(&g_CurrentPlayer->health_display_values[0].items[0]), 0x2e);

    lookatmtx = dynAllocateMatrix();
    orthomtx = dynAllocateMatrix();

    guOrtho(orthomtx, -800.0f * D_800364CC, 800.0f * D_800364CC, -600.0f * D_800364CC,
            600.0f * D_800364CC, -100.0f, 1000.0f, 1.0f);

    gSPMatrix(gdl++, osVirtualToPhysical(orthomtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);

    matrix_4x4_set_lookat_target(&lookatmtxf, 0.0f, 500.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f);
    matrix_4x4_f32_to_s32(&lookatmtxf, (Mtxf*) lookatmtx);

    gSPMatrix(gdl++, osVirtualToPhysical(lookatmtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    gDPPipeSync(gdl++);
    gDPSetCycleType(gdl++, G_CYC_1CYCLE);
    gDPSetRenderMode(gdl++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetAlphaCompare(gdl++, G_AC_NONE);
    gDPSetCombineMode(gdl++, G_CC_SHADE, G_CC_SHADE);
    gDPSetPrimColor(gdl++, 0, 0, 0xe6, 0xe6, 0xe6, 0x00);
    gSPClearGeometryMode(gdl++, G_CULL_BOTH);

    gSPDisplayList(gdl++, OS_PHYSICAL_TO_K0(&g_CurrentPlayer->watch_body_armor_bar_gdl));
    gSPDisplayList(gdl++, OS_PHYSICAL_TO_K0(&g_CurrentPlayer->watch_health_bar_gdl));

    gSPMatrix(gdl++, osVirtualToPhysical(currentPlayerGetProjectionMatrix()),
              G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);

    return gdl;
}

/* =========================================================================
 * SLICE 5 — a fence in front of the first-person view model
 * =========================================================================
 * Symptom: the gun's slide leaves a ghost as it cocks back, and the hand chop
 * leaves a faint duplicate hand above the arm. A GHOST, not a flicker — so the
 * view model is still being interpolated, which after slice 4 means something
 * is handing it a real id.
 *
 * It inherits one. Slice 1 tags room geometry and never closes the group,
 * because applyRoomMatrixToDisplayList returns before its caller emits the
 * geometry — there is no "after" to close in. So everything drawn once the
 * world pass is done, the first-person gun and hands included, is still
 * claiming the last room's identity. RT64 then pairs the hand's vertex buffer
 * with whatever else carried that id and lerps between them, which is exactly a
 * faint hand hovering where no hand is.
 *
 * gunRenderCasings runs immediately before gunRenderFirstPersonGunModels on the
 * same Gfx pointer (bondview2.c:8953-8954), and is fifteen lines. That makes it
 * the cheap place to drop a fence. gunRenderFirstPersonGunModels itself is 112
 * lines and leans on struct fields absent from patches/structs.h — transcribing
 * it to add one tag is how you break something that currently renders fine.
 *
 * This makes the view model render as-is at native rate: correct, and stepped.
 * Giving the two hands proper per-hand ids with vertex interpolation is the
 * better end state and needs that 112-line function; see the plan doc. Do it
 * only if the stepping actually reads badly, since the gun is always on screen.
 *
 * CasingRecord is redeclared here because patches/structs.h lacks it. Layout is
 * the VERSION_US branch of lib/ge/src/game/gun.h:242 — 160 bytes. If casings
 * misbehave, suspect this layout first.
 */
typedef struct GeCasingRecord {
    f32 floor_y_pos;
    coord3d pos;
    coord3d vel;
    Mtxf rot_mtx;
    Mtxf rot_velocity_mtx;
    ModelFileHeader* header;
} GeCasingRecord;

extern GeCasingRecord g_Casings[20];
void sub_GAME_7F068EC4(GeCasingRecord* entry, Gfx** gdl);

#ifndef GE_INTERP_VIEWMODEL_FENCE
#define GE_INTERP_VIEWMODEL_FENCE 1
#endif

RECOMP_PATCH void gunRenderCasings(Gfx** gdl) {
    GeCasingRecord* end = g_Casings + 20;
    GeCasingRecord* entry = g_Casings;

    while (entry < end) {
        if (entry->header) {
            sub_GAME_7F068EC4(entry, gdl);
        }

        entry++;
    }

#if GE_INTERP_VIEWMODEL_FENCE
    /* Everything from here to the next tagged draw renders as-is. */
    gEXMatrixGroupNoInterpolation((*gdl)++, G_EX_NOPUSH, 0, G_EX_EDIT_NONE);
#endif
}

/* =========================================================================
 * SLICE 6 — bullet impacts get their own id band, and fence the pass
 * =========================================================================
 * Bullet holes are decals stuck to a wall. They never move. They should be the
 * easiest thing in the renderer, and they are not, because of how they reach
 * the display list.
 *
 * explosionRenderBulletImpactOnProp (explosion.c:2201, ~95 lines) walks
 * g_BulletImpactBuffer and batches by room:
 *
 *     if (var_s5 != g_BulletImpactBuffer[i].room) {
 *         var_s5 = g_BulletImpactBuffer[i].room;
 *         gdl = applyRoomMatrixToDisplayList(gdl, g_BulletImpactBuffer[i].room);
 *     }
 *     ... gSPVertex + gSP2Triangles per impact ...
 *
 * So every bullet hole in room R is drawn under id R + 1 — the SAME id as R's
 * own walls, and the same id explosionRenderScorchBuffer (explosion.c:1888),
 * explosionRenderPropExplosion (:886) and the smoke path (:1499) hand out. Four
 * unrelated kinds of geometry claiming one identity is precisely the collision
 * slice 1 was built to remove, reintroduced one level down.
 *
 * Batching by room is NOT the problem and is not worth changing. Every impact
 * in a room shares one matrix, so one group per room is the correct shape —
 * the same shape that made room walls rock stable. What is wrong is which
 * namespace that group lives in.
 *
 * THE FIX, and why it is in the wrapper.
 *
 * explosionCallRenderBulletImpactOnProp (explosion.c:2299) is four lines:
 *
 *     Gfx *explosionCallRenderBulletImpactOnProp(Gfx *arg0) {
 *         return explosionRenderBulletImpactOnProp(arg0, NULL, 0);
 *     }
 *
 * It is the world-geometry entry point — bg.c:678, the arg1 == NULL path, the
 * one that walks rooms rather than props. Patching it costs nothing and risks
 * nothing, where transcribing the 95-line worker to move one tag risks
 * everything. Set the bias on the way in, clear it on the way out.
 *
 * AND, because this wrapper CONTAINS its own draw, it can close its own group —
 * the structural rule that caused three separate bugs in slices 2 and 5.
 * applyRoomMatrixToDisplayList cannot fence itself, because it returns before
 * its caller emits any geometry. This wrapper can, and does.
 *
 * That fence is worth more than it looks. bg.c:677-678 is:
 *
 *     gdl = explosionRenderScorchBuffer(gdl);
 *     gdl = explosionCallRenderBulletImpactOnProp(gdl);
 *
 * so the fence also catches the scorch pass's leak on the way past, for free.
 * Note that slice 4 does NOT save us here: it demotes untagged AUTO world
 * groups to IGNORE, and a leaked room id is a real id, not AUTO.
 *
 * Ordering: impacts are paired frame to frame by position within the group
 * (G_EX_ORDER_LINEAR), and the buffer is walked in index order, so the pairing
 * is stable while an impact lives. It shifts when a slot is recycled, which
 * costs one frame of a wrong pair on a decal that does not move. Acceptable.
 *
 * EXPECTED RESULT: bullet holes stop sliding across walls and stop dragging the
 * room's geometry toward them. If they instead start FLICKERING, the pass is
 * failing to pair at all — set GE_INTERP_BULLET_IMPACTS to 0 and they revert to
 * inheriting the room's id, which is where they were before this slice.
 */

Gfx* explosionRenderBulletImpactOnProp(Gfx* gdl, PropRecord* prop, s32 withalpha);

#ifndef GE_INTERP_BULLET_IMPACTS
#define GE_INTERP_BULLET_IMPACTS 1
#endif

RECOMP_PATCH Gfx* explosionCallRenderBulletImpactOnProp(Gfx* gdl) {
#if GE_INTERP_BULLET_IMPACTS
    g_geRoomIdBias = GE_IDBAND_BULLET_IMPACT;
    gdl = explosionRenderBulletImpactOnProp(gdl, NULL, 0);
    g_geRoomIdBias = GE_IDBAND_ROOM;

    /* Everything from here to the next tagged draw renders as-is. Also fences
     * the scorch pass that ran immediately before us. */
    gEXMatrixGroupNoInterpolation(gdl++, G_EX_NOPUSH, 0, G_EX_EDIT_NONE);

    return gdl;
#else
    return explosionRenderBulletImpactOnProp(gdl, NULL, 0);
#endif
}
