# PRIOR-ART

Credits owed for prior art that influenced GEVR designs. Required before the first public push (see `PUBLISH-MANIFEST.md` in the private workspace).

## Alex-LeTux/perfect_dark_VR (MIT)

- Repository: https://github.com/Alex-LeTux/perfect_dark_VR
- Branch surveyed: `port`
- Commit: `67ea20c86986c6bc85687f26a27418b266af309c`
- Licence: MIT (Ryan Dwyer's Perfect Dark decomp copyright plus the VR fork's)

That checkout is **not** vendored here. It was read locally as prior art only.

### Influence already recorded in this tree

Designs / constants informed by that work (details in `docs/102`, `docs/160`, and `docs/81`):

- Controller basis of the form `{w, -x, y, -z}` (`-HandAxis*`)
- Pistol grip offset `(0, 16, -4)` scaled to `-GunOffY 8 -GunOffZ -2`
- `x/(1-damp)` integrator pre-load
- Drawn-vs-shot clamp split

The MIT notice travels with anything derived from it. See also `docs/55-prior-art-licence-check.md` and `docs/81-prior-art-perfect-dark-VR.md`.
