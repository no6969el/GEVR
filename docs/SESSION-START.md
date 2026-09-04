# SESSION-START — WHAT THE OWNER SUPPLIES, AND THE PROMPT

**Companion to `00-STATE.md`. Updated 2026-08-30d.**

---

## 0. "YOU" AND "THE OWNER" MEAN THE SESSION LEAD, NOT AN ACCOUNT
**This project is run under more than one username, account and machine.** Everywhere these
docs say *the owner* or *you*, read **whoever is leading the current session** — identified
by the prompt, never by a login. **`00-STATE.md` §0 is the full rule.** The two consequences
that bite in practice:
1. **No command may hardcode a username or home directory.** Use `$env:USERPROFILE`,
   `$env:APPDATA`, `$HOME`. Project paths (`F:\Projects\GEVR\...`) are username-free and
   stay absolute (§1b).
2. **The per-user config in `$env:APPDATA` is DIFFERENT FOR EACH LOGIN**, and it is the live
   one (`00-STATE` §6). A knob "parked" under one login is not parked under another —
   that already cost a session once (`262` §2).

## 1. WHAT YOU SUPPLY

**Normally: NOTHING but the prompt.** The folders `Z:\Desktop\GoldenEyeVR` and
`Z:\Desktop\GoldenEye64Recomp` are connected to the session; the assistant reads
the tree itself. **Do NOT paste document paths** — that was the old habit and it
cost 5,300 lines of context before a word of work.

**Supply only when it applies:**
- **The name of the newest run log**, if you ran something since last session
  (e.g. *"run_texbind.log is from this morning"*). It can find the file; it
  cannot know which run you meant.
- **A screenshot**, for anything visual. A wear report outranks a log.
- **Anything you changed by hand** — a cfg edit, a deleted save, a driver update,
  a different headset. **Silent environment changes have cost this project whole
  sessions** (`40`).

## 1b. ►►►► WHAT THE ASSISTANT MUST SUPPLY: EVERY COMMAND, COMPLETE ◄◄◄◄

**STANDING RULE, ADDED 2026-08-30 AT THE OWNER'S REQUEST. IT IS NOT OPTIONAL.**

**Never describe an action the owner has to perform. Give the command.** And give
it as a **single, self-contained, copy-paste block** that works in a window the
assistant has never seen:

1. **Absolute paths. Always.** Never a path relative to a directory the assistant
   merely assumes is current. **But NEVER a hardcoded username or home directory** —
   `$env:USERPROFILE` / `$env:APPDATA` / `$HOME` instead, because the login changes between
   sessions (§0). `.\local-only\save-backup.ps1` cost a round trip on
   2026-08-30 for exactly this reason -- the owner was in `build-windows`.
2. **The environment reset goes IN the block**, not in prose above it.
   `Remove-Item Env:GETV_* -ErrorAction SilentlyContinue` is the first line of
   every block that sets a `GETV_*`. **`$env:` persists, and the owner runs
   multiple windows** -- a variable left over from another window is invisible and
   silently changes the run.
3. **One block per action.** Not a paragraph with commands embedded in it, and not
   one giant block for three different runs. The owner copies, pastes, and reads
   the result -- that is the whole interaction.
4. **Every variable the run depends on is set explicitly in the block**, including
   the ones that "should already be right". Assume nothing is set. Assume nothing
   is left over.
5. **End the block with its own verification** where one exists -- the exe's
   timestamp, the `GETV_*` actually in the environment, the banner that proves the
   knob took. **A silently-ignored knob reads as a clean null result** (`133`, and
   `268` §4).

> **The failure this prevents is not the owner's forgetfulness. It is the
> assistant handing over an instruction instead of an instrument.** Rule `14`
> already says do not ask the owner to read a file the source can print; this is
> the same rule pointed at the shell. **If the owner has to reconstruct anything,
> the command was not finished.**

## 2. THE PROMPT

Paste this, then add your task on the last line.

```
Read repo\docs\00-STATE.md first and nothing else until it points you somewhere.
It is the entry point; HANDOVER and 00-START-HERE are history and reference.

Working rules for this session:
- Measure, do not describe. Build the instrument before the candidate, and say
  what it would print if it were pointed at the wrong thing BEFORE the run.
- We have all the source. Change the source rather than working around it, and
  never ask me to read a file the program could print.
- One behaviour change per build. Diagnostics may be batched.
- Write the gate before the code, and tell me what would falsify you.
- Every commit is mine. Delete nothing; knobs stay reachable.
- Anything you infer is [INFERRED] and may not be built on. If you have not
  verified it this session, say so.
- Plan, then stop and check with me before building.
- Tell me when I should start a fresh session, without me asking.
- Give me every command as a complete copy-paste block: absolute paths, the
  env reset included, one block per action. I run multiple windows.

At the end of the session update 00-STATE.md: section 3 (state), section 4 if
anything was retracted, section 5 if a theory died, and the currency line.

Task:
```

### THE ONE-LINE VERSION, WHEN YOU JUST WANT TO CONTINUE
```
Read repo\docs\00-STATE.md and continue from section 3. Same rules as always.
Plan first, stop before building.
```

## 3. WHAT TO EXPECT BACK, AND WHAT TO PUSH ON
A good first response names **what it read, what it is treating as true, and what
it does not know yet.** Push back when you see:
- **A confident claim with no doc or measurement behind it.** Ask *"measured or
  inferred?"* — `263` §1 was six invented faults that one question would have caught.
- **A fix proposed before an instrument.** Ask what would falsify it.
- **A second change added to a build.** Say *"one thing."*
- **A request that you go read something.** The source can usually print it.
- **A command that is not copy-paste ready** -- a relative path, a missing
  `Remove-Item Env:GETV_*`, or an action described in prose. Say *"give me the
  block."* See §1b.
- **Anything you have reported more than once still not being worked.**
  Rule `16`: repetition is a ranking error, and the ranking is what gets fixed.

## 4. REASONING EFFORT, AND WHERE THE BUDGET ACTUALLY GOES

### **RUN MEDIUM BY DEFAULT.** Low is a false economy on this project.
`[MEASURED]` against the 2026-08-29 session: almost none of the assistant's
errors were reasoning-DEPTH failures. They were discipline failures — reading a
log still being written, generalising six faults from two screenshots, checking
three config paths and not the live fourth, placing a trace AFTER the gate it
existed to observe. **Low effort's failure mode is exactly that: pattern-jumping
and thin verification.** And a wrong diagnosis here is not cheap — it costs a
build, a run, and the owner's time at the machine.

### **THE BIGGEST COST IS CONTEXT, NOT REASONING.**
That session's largest single expense was **5,300 lines of documents pasted at
startup before any work happened**, plus a 28 MB log and re-greps for things
already found. **`00-STATE.md` cuts orientation from ~5,300 lines to ~170.**
**Targeted greps instead of whole-file reads save more than any effort setting,
and cost no accuracy.** Fix context first; only then think about the dial.

### MATCH THE DIAL TO THE TASK
| effort | use for |
|---|---|
| **LOW** | mechanical work — run a grep, check a symbol is in the binary, apply a patch already designed together, write up findings already established |
| **MEDIUM — the default** | the project's core loop: read a log and diagnose, design an instrument, plan a change, form a hypothesis from evidence |
| **HIGH — a handful of times in the whole project** | long-consequence decisions where being wrong means REWORK, not a re-run. Identifiable in advance: the stereo architecture choice (`258` §1), the pose-spine design under `P6`-`P9`, the `P1`/`P9` determinism question. **NOT debugging.** |

> **The assistant should SAY when a task is worth switching up for, rather than
> the owner having to guess.** Flagging it is part of the job.

## 5. ►►►► WHEN TO START A NEW SESSION — THE ASSISTANT SAYS SO, UNPROMPTED ◄◄◄◄

**STANDING RULE, ADDED 2026-08-30 AT THE OWNER'S REQUEST.**
**The owner should never have to guess whether the session has gone stale. Flagging it is
part of the job, exactly as flagging the reasoning dial is (§4).**

### THE HONEST CAVEAT, FIRST
**The assistant CANNOT see an exact context figure and must not invent one.** Never say
"we are at 60%". Judge by SYMPTOMS AND COUNTS, and say which one triggered the call:
- **how many large artefacts have been read this session** — run logs, whole source files,
  multi-hundred-line docs. **A 28 MB log or three run logs is the usual trigger.**
- **re-reading.** Grepping for something already found, or re-opening a file already read,
  is the first observable symptom of a session that has lost its own earlier work.
- **summarising where it used to quote.** Losing the ability to cite an exact line number
  or figure from earlier in the session.

### THE FOUR MOMENTS TO CALL IT
1. **A finding is documented and committed.** A numbered doc written, `00-STATE` updated,
   the owner's commit run. **That is a clean seam and the cheapest possible place to break.**
2. **The next task is a different KIND of work.** Debugging -> design, or anything §4 marks
   **HIGH** (`258` §1's stereo architecture, the `P6`-`P9` pose spine, the `P1`/`P9`
   determinism question). **A long-consequence design decision deserves a session whose
   whole context is that decision** — not one carrying three run logs and a dead theory.
3. **The session has been chasing ONE fault and the fault has moved.** New symptom, new
   subsystem, new arm — the accumulated context is now mostly about the old shape.
4. **Any of the symptoms above appear**, whatever else is happening.

### WHAT THE SUGGESTION MUST CONTAIN — A POINTER IS NOT A HANDOFF
**Do not suggest a new session until the handoff is COMPLETE**, or the owner pays twice:
- **`00-STATE` §3/§4/§5 and the currency line updated**, and the numbered doc written.
- **The exact one-line prompt to paste** (§2), plus **the names of any run logs the new
  session will need** — the owner supplies nothing else (§1).
- **One sentence on what the new session should do FIRST**, so it does not re-derive
  what this one already established.
- **Anything owed that is not yet in a doc** — an unanswered decision, an untested knob.

> **The failure this prevents is a session that quietly degrades and starts costing more
> than it produces.** `[MEASURED]` 2026-08-29: the single largest expense of that session
> was context, not reasoning (§4). **A clean break is cheaper than a long tail.**

## 6. AT THE END OF A SESSION
- **►► THE COMMIT MESSAGE FILES — ONE PER REPO TOUCHED, DATED TODAY. RULE `17`. ◄◄**
  `COMMIT-MESSAGE-<yyyy-mm-dd>.txt` (docs), `-native.txt`, `-decomp.txt` as applicable.
  **`COMMIT-NOW.cmd` takes the NEWEST by timestamp, so a missing file silently commits under
  the LAST session's message** — it did that three times running on 2026-08-30. The script now
  refuses when the subject already matches HEAD, **but writing the file is the assistant's job,
  not the guard's.** A session is not ready to commit until its messages exist.
- **A numbered doc** for the findings (`264` next).
- **`00-STATE.md` updated** — §3, §4, §5, currency line.
- **`HANDOVER` top banner** for what happened, chronology preserved.
- **Then YOU commit** — `COMMIT-NOW.cmd`, main PC, not the bridge.
  **`fetch-thirdparty.sh regen` before the native half** — `gfx_pc.c`, `gfx_sdl2.c` and
  `gfx_opengl.c` are gitignored and reach git only through the patch. **FROM GIT BASH, not
  MSYS2's bash (it has no `git`), and not over the bridge. The gate is `verify` reporting
  `15/15 files match pristine + patch`.** Full block: `MAIN-STATION-TASKS.md`, top. `271` §7.
