# 239 — TWO OF MINE TO RETRACT: THE WRONG SFX KNOB, AND A GLOBAL SWITCH SOLD AS A DEFAULT

**2026-08-28. Docs run to `239`. NEXT DOC = `240`.**

> `[REPORTED]` ***"I heard the gunfire when I hit the b button, but everything
> looks weird too. It does not look right. and the latency is here again. That
> last build that I ran didn't have it... You caused it. Correct?"***
>
> # ►►►► **THE BINARY IS UNCHANGED. THE ENVIRONMENT IS NOT. AND BOTH SUSPECTS
> # ARE MINE.** ◄◄◄◄

---

## §1 — FIRST, WHAT IS NOT AT FAULT

`[MEASURED]` `goldeneye.exe` is **21:22:13** — **byte-identical to the run the
owner called better.** No build has happened since `G-234`. **The slot fix, and
every line of code changed this session, is common to both the good run and the
bad one and CANNOT be the difference.**

**The difference is entirely environment and config, and I supplied both.**

---

## §2 — SUSPECT 1: `GETV_AUDIO_DEBUG=1` WAS THE WRONG KNOB AND IT IS NOT CHEAP

`[MEASURED]` `run_sfx.log`: **3,975,000 bytes, 36,291 lines, of which 11,194 are
`audiodbg`** — roughly one line in three, emitted **per audio frame**, through
`osSyncPrintf` and redirected to disk.

`229` §13 `[MEASURED]` that this port's stdout was a discarded handle until that
session fixed it. **It is a real, synchronous, buffered write now**, and eleven
thousand of them inside the audio path over a single session is a plausible
source of exactly the symptom reported. **`[INFERRED]`, and the test is one plain
run.**

### §2.1 — AND IT COULD NEVER HAVE ANSWERED THE QUESTION

`[READ]` `GETV_AUDIO_DEBUG` prints **mixer statistics** — `f/n/q/cmd`, `rmsL/rmsR`,
`pk`, the `load/adpcm/resample/envmix/mix` chain, `vsvol`, `envmix` targets.
**`[MEASURED]` it emitted ZERO sound-index lines: `grep -i sfx` over 36,291 lines
returns one boot mark and nothing else.**

> **`229` §20 item 2 NAMED THE RIGHT INSTRUMENT AND I SENT A DIFFERENT ONE.**
> The item says `GETV_AUDIO_TESTSFX=<id>` — *"Try a handful of ids and say what is
> heard. A constant offset and a scramble need completely different fixes."*
> **`GETV_AUDIO_DEBUG` measures the MIXER; the fault is in the INDEX. A run was
> spent on the wrong layer.**

`[READ]` **`GETV_SFXWHY` is not it either** (`snd.c:990`): it fires only when
`soundArray[soundIndex]` is **NULL** — a MISSING sound, not a WRONG one. Our sound
plays; it is the wrong one. **Recorded so the next session does not reach for it.**

---

## §3 — SUSPECT 2, AND THIS ONE IS THE LIKELIER AND THE WORSE

**`238` §2 told the owner to put `GETV_RGBA16BE = 1` in `goldeneye.cfg`, where it
applies to EVERY RUN AND EVERY RGBA16 TEXTURE IN THE GAME.**

`[READ]` upstream's `COLOUR_BUGS.md` says in as many words why it is **not** a
default:

> **"The census has no coverage."** Five levels compared byte-identical **because
> `GETV_LIGHTTRACE` reports zero RGBA16 uploads in those idle frames.** *"The only
> RGBA16 consumer observed anywhere is the explosion flare."*

**`238` §2 quoted that paragraph and then recommended persistence anyway.** The
reasoning offered — that the config file keeps the off-switch reachable — is true
and **beside the point**: an untested global byte-swap is not made safe by being
easy to turn off. **"Nothing else measured uses RGBA16 yet" is a statement about
the MEASUREMENT, not about the game**, and a level with real RGBA16 content is
exactly where it would first go wrong.

> ## ►► *"everything looks weird"* IS WHAT A GLOBAL BYTE-SWAP OF AN UNSURVEYED
> ## TEXTURE FORMAT WOULD LOOK LIKE. ◄◄
> **`[INFERRED]`. Counter-example search: `GETV_AUDIO_DEBUG` (§2) also fits
> "everything feels off" via frame cost, and the owner ran both at once, so the
> two are CONFOUNDED in this report and neither is established. `48` again: two
> behaviour changes in one run.**

**AND THE CONFOUND IS MINE TOO** — `238` §2's config line and `238` §4's
`GETV_AUDIO_DEBUG` run were handed over together, with no instruction to separate
them.

---

## §4 — `G-239`. UNPICK IT, ONE AT A TIME, NO BUILD.

**A — remove the persistent term first, because it is the one that survives runs.**
Comment the line out; do not delete it, so it stays on file:
```ini
# GETV_RGBA16BE = 1   # docs 237/239: explosion-only, NOT safe as a global default
```
Then a completely plain run, **no `GETV_*` at all**:
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd C:\Users\pdbar\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
.\goldeneye.exe
```
**Run around. Judge LOOK and LATENCY separately.**

| result | conclusion |
|---|---|
| both back to normal | **the cfg line was the fault.** `GETV_RGBA16BE` returns to a per-run env var, used only when an explosion is the subject |
| look fixed, latency remains | the latency is `GETV_AUDIO_DEBUG`'s cost, and it is gone the moment that knob is unset — **which this run already proves, since it is unset here** |
| neither fixed | **both of my suspects are wrong** and something else changed between 21:22 and now. **Say so and I start again from the binary.** |

**B — and only then, the SFX, with the instrument the corpus actually named:**
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$env:GETV_AUDIO_TESTSFX = "<id>"
.\goldeneye.exe
```
**`GETV_AUDIO_DEBUG` is NOT set for this** — it answers a different layer and costs
the run. Ids to be chosen from `sndPlaySfx`'s table before the run, not guessed at
the keyboard.

---

## §5 — THE RULE THIS EARNS

> **A KNOB VALIDATED ON ONE OBJECT IS NOT A SETTING. `237` measured
> `GETV_RGBA16BE=1` against AN EXPLOSION FLARE and `238` promoted it to EVERY
> FRAME OF EVERY LEVEL.** The measurement was sound and its scope was not.
> **Before making a term persistent, state what it was measured on and what it now
> applies to. If those differ, it is still a knob.**

**And `HANDOVER` §5 holds again: the owner's *"you caused it"* was directed at the
right session and, on the evidence in §1, at the right layer — the environment I
handed him, not the code.**
