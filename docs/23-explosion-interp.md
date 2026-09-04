# Explosions stick to the view when you turn — pre-existing, and not Phase 1

**2026-08-22. Logged, not fixed.**

## Observation

Barrel explosion effects appear in front of the player after a fast turn, as
though anchored to the view rather than to the world.

## Attribution, by A/B

| Build | Result |
|---|---|
| `GE_VR_MODE_HOSTEYE`, `GE_VR_FRUSTUM=1` | present |
| `GE_VR_MODE_HOSTEYE`, `GE_VR_FRUSTUM=0` | present |
| `GE_VR_MODE_OFF` | present, **and worse** |

**Not ours.** No VR code path affects it, and turning the VR patch off entirely
makes it more noticeable rather than less.

### One correction to how that test was described

`GE_VR_MODE_OFF` was called "fully stock" when the runs were proposed. It is not.
It disables the VR patch only. `interpolation.c` and the `rt64_game_frame.cpp`
matrix-tagging change are both still active in that build. The A/B therefore
isolates the VR work, which is what was wanted, but it does **not** establish that
the artifact exists in an unmodified upstream tree. It establishes that it lives
below the VR layer.

### Why narrower is worse

A mispaired interpolation produces a fixed positional error in world space. The
same error covers a larger fraction of the screen at 60 degrees than at 106, so
the wide FOV makes it less noticeable without making it any less wrong. That is
camouflage, not improvement.

## Where it lives

The interpolation layer — `04-interpolation.md`, and already on `05`'s open list
as "Glass / particles / blood ids, small each". The mechanism is the one slice 6
addressed for bullet impacts: RT64 pairs matrices between frames to interpolate
them, and effects sharing an id space with unrelated geometry get paired with the
wrong previous matrix. The interpolation then lerps between two unrelated
transforms, and the visible result is exactly this — something sliding across the
world instead of staying put.

`interpolation.c` already has the fix pattern:

```c
#define GE_IDBAND_ROOM          0x00000000
#define GE_IDBAND_BULLET_IMPACT 0x00010000

RECOMP_PATCH Gfx* explosionCallRenderBulletImpactOnProp(Gfx* gdl) {
    g_geRoomIdBias = GE_IDBAND_BULLET_IMPACT;
    ...
    g_geRoomIdBias = GE_IDBAND_ROOM;
}
```

The barrel fireball is a different renderer. Candidates, from
`lib/ge/src/game/explosion.c`:

| Function | Line | Likely role |
|---|---|---|
| `explosionRenderPropExplosion` | 851 | the fireball on a destroyed prop — **prime suspect** |
| `explosionRenderPart` | 929 | one sprite of the above |
| `explosionRenderPropSmoke` | 1468 | trailing smoke |
| `explosionRenderFlyingParticles` | 1711 | debris |

A new `GE_IDBAND_EXPLOSION` around `explosionRenderPropExplosion` is the same
shape of change as slice 6, which `05` sizes as small.

## Why it matters more in VR than the flat symptom suggests

An effect that fails to stay put when the head turns is one of the more
unpleasant things a headset can show, because it contradicts the vestibular
system directly rather than merely looking wrong. This cannot ship unfixed. It is
still not Phase 1: stereo does not depend on it, and it predates all of it.

Logged as the next interpolation slice.
