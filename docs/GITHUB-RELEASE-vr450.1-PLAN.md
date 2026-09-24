# GEVR Beta vr450.1 — release plan (BarZ)

**Status:** **SHIPPED** — tag `vr450.1` is GitHub Latest. Smoke PASS. **vr450** and **vr445.2** left intact.  
**Latest:** [vr450.1](https://github.com/no6969el/GEVR/releases/tag/vr450.1) — zip `GEVR-Beta-vr450.1-win64.zip`.  
**Prior (history):** [vr450](https://github.com/no6969el/GEVR/releases/tag/vr450) · [vr445.2](https://github.com/no6969el/GEVR/releases/tag/vr445.2) — do **not** delete/retag.

**Living status:** [`gevr-living-status.md`](gevr-living-status.md)  
**Release body:** [`GITHUB-RELEASE-vr450.1.md`](GITHUB-RELEASE-vr450.1.md)

---

## Why `vr450.1` (not a full 451)

- **vr450** shipped RECT + GRIPUSE + slot4; BarZ pulled **GRIPUSE** from Latest pending further testing.
- Point cut: same ship as 450 minus `GETV_VR_GRIPUSE` default-on.

---

## Must-not (standing)

| Do not | Why |
|--------|-----|
| Delete / retag / force-push `vr450` or `vr445.2` | Testers and history |
| Default-on GRIPUSE | Needs further testing (#90) |
| Ship TEXGUARD / SCRAPDROP / EMBEDEYE / FRIGMUTE / FRIGDOORROOM / grip pickup | HOLD |

---

## 1. KEEP — default-on at vr450.1 bake (LOCKED)

| Item | Tracker / knob | Bake default |
|------|----------------|--------------|
| **445.2 KEEP stack** | #74 playspace · #75 melee · #82 Janus · gun origin · #84 walk/run · cadence · SKYWORLD · ANIMFRAMES · MODEMDROP=3 | **ON** |
| **Frigate water RECT** | #80 · `GETV_VR_SKYWATERRECT` | **ON** (LERP/LAYER OFF) |
| **Save slot 4 seed** | `GETV_SEEDFOLDER4` (C-default ON; empty FOLDER4 only) | **ON** (as vr450) |

**Locked KEEP lines:**

```
KEEP vr450.1: 445.2 stack default-on (#74 playspace · #75 melee · #82 Janus · gun origin · #84 walk/run · cadence · SKYWORLD · ANIMFRAMES · MODEMDROP=3 temp).
KEEP vr450.1: GETV_VR_SKYWATERRECT default-on (#80). LERP/LAYER stay OFF.
KEEP vr450.1: GETV_SEEDFOLDER4 slot4 seed (007+cheats empty FOLDER4; slots 1–3 safe).
REMOVE / OFF: GETV_VR_GRIPUSE (#90 needs further testing; not in 450.1). Squeeze = AIM.
```

---

## 2. REMOVE / default OFF

| Item | Why |
|------|-----|
| **GETV_VR_GRIPUSE** | Needs further testing; unset/0 so squeeze = AIM like pre-450. Code may remain in tree. |

---

## 3. HOLD — not in bake

Grip pickup / mines / modems · FRIGMUTE · FRIGDOORROOM · TEXGUARD / SCRAPDROP / EMBEDEYE · SKYWATERLERP/LAYER · #70 / #79 FAIL chairs

---

## 4. BarZ one-liner (SHIP)

**SHIP vr450.1:** KEEP = 445.2 stack + SKYWATERRECT#80 + slot4 · **GRIPUSE OFF** (#90 further testing) · leave vr450 + vr445.2 published.
