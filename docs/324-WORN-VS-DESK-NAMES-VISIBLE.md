# 324 -- WORN vs DESK NAMES WHAT MADE THE SESSION VISIBLE

2026-09-05. Helper-run control on the main PC. Same gevr_xr_slice4.exe both times
(md5 005D52937891280473E8204D48928728). No product source edited. No new harness.
Predictions written first in PLAN-324-VISIBLE.md.

## 0 -- ONE TABLE

| | |
|---|---|
| 1 | V-desk LANDS. Desk, HMD awake not worn: Arm A shouldRender 0/570; READY->SYNCHRONIZED only; X4 half highest SYNCHRONIZED. Reproduces 322. |
| 2 | V-worn LANDS. HMD on head (owner confirmed): Arm A shouldRender 570/570; READY->SYNCHRONIZED->VISIBLE at frame 1; X4 half VISIBLE. Reproduces 323. |
| 3 | Same binary both runs. Outside-tree factor named: worn vs desk. |
| 4 | VISIBLE does not require submit. Worn + layerCount 0 reaches VISIBLE. Desk + 600 layers stayed SYNCHRONIZED. |
| 5 | 323 X4-2 causal claim stays withdrawn. Harness string is stale; not re-run to tidy. |
| 6 | D-X3 not started. Numbers taken while VISIBLE must be labelled as worn-condition unless desk-controlled. |

## 1 -- WHY IT GATED THE OTHERS

Every 323 headline number was taken in a VISIBLE session for an unnamed reason.
Until worn/desk was named, those numbers could have been condition artifacts.
They are now: worn unlocks shouldRender/VISIBLE; desk locks 322-like behavior.

## 2 -- WHAT THIS DOES NOT CLAIM

- Not that submit never matters for compositing quality.
- Not that D-X3 is built.
- Not a stereo claim (no owner colour call required on desk; worn may have shown red/blue again -- not scored).
- Not H19 fixed. Wrong filed fixes stay FIVE.

## 3 -- ARTIFACTS (gitignored reports OK)

- repo/xr/gevr_xr_slice4_324a_DESK_report.txt + _conditions.txt
- repo/xr/gevr_xr_slice4_324b_WORN_report.txt + _conditions.txt
- 323 gevr_xr_slice4_report.txt left as historical evidence

169 NEXT ID = U-28. NEXT INSTRUMENT HOLE = H25.