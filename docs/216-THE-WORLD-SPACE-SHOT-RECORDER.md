# 216 — THE WORLD-SPACE SHOT RECORDER. THE OWNER ASKED FOR IT AND THE DATA REQUIRES IT.

**2026-08-26. Tiers per `182`. `[INFERRED]` carries its counter-example search
(`209` §4.3). BUILT, UNRUN.**

---

## §1 — THE REPORT THAT MAKES IT NECESSARY

> `[REPORTED]`: ***"I turned around, and I shot upwards, and it shoots to the
> left. I shot upwards to the right, and it shot to the LEFT of the gun, which is
> totally off of what's normally happening when I shoot forward."***

**`215` §1 established the forward case: a CONSTANT LINEAR MISS equal to the
muzzle-to-eye offset, because the two rays are PARALLEL. THAT EXPLANATION CANNOT
PRODUCE THIS ONE.** A constant offset is the same displacement whichever way you
face — **it has no way to know you turned around or aimed up.**

> **SO THERE ARE (AT LEAST) TWO FAULTS, NOT ONE:** a parallel-ray offset in the
> forward case, and **something DIRECTION-DEPENDENT** — a frame or rotation
> error — that appears off-axis. **`[INFERRED]`, and the counter-example search
> is what motivated this document: I looked for a single mechanism that produces
> BOTH a distance-constant miss forward AND a direction-flipping miss up-right,
> and did not find one.** Two mechanisms, and **nothing currently logged can
> separate them**, because every existing instrument is in CAMERA space and the
> question is about direction in WORLD space.

---

## §2 — THE OWNER'S REQUEST, AND WHY IT IS THE RIGHT INSTRUMENT AGAIN

> `[REPORTED]`: ***"build something that puts us in the space and we understand
> all the values of the space around us... I would do a run, and you would know
> all the steps that I took, where I was, how my arm position was relative to the
> wall or the character. All that data would be so cool. Do you agree?"***

**YES — AND IT IS THE METHOD THAT HAS WORKED EVERY TIME ON THIS PROJECT.**
`200` solved the seam composition from a recording after two wear tests failed.
`203` solved the consuming frame from a recording. `212` settled U-18 from a
read. **Every guess-and-wear cycle this month has cost a session; every
measurement has closed a question in one.**

---

## §3 — WHAT IS LOGGED, AND WHY NO CAMERA MATRIX IS NEEDED

**`168` §5's GREP, RUN FIRST: `currentPlayerGetViewToWorldMtxf` is NOT in
`externs.h`.** The obvious route — convert our camera-space values to world — is
**blocked.**

**BUT THE GAME ALREADY KEEPS EVERYTHING WE NEED, IN WORLD SPACE:**

| value | source | `[READ]` |
|---|---|---|
| the gun's world POSITION and ORIENTATION | `hand->throw_item_pos_related` | `structs.h:1734`; `gunfire.c:574` builds it as `ViewToWorld x gunmtx_camspace` |
| the bullet's IMPACT point | `hands[].item_related` | `structs.h:1795`; `gunSetTracerTarget` |
| the PLAYER's position | `g_CurrentPlayer->pos` | `structs.h:1879` |

**ALL THREE ARE ALREADY IN ONE FRAME, SO THE CONVERSION IS NOT NEEDED AT ALL.**
The actual bullet vector (`impact - gunpos`), the gun's true pointing
(`gunfwd`), and the angle between them are computable offline — **which is
exactly the residual §1 cannot otherwise separate.**

```
[gevr] SHOTWORLD gunpos=(x,y,z) gunfwd=(x,y,z) previmpact=(x,y,z) player=(x,y,z)
```

**Emitted beside `SHOTREC` inside the fire path**, so both lines are from the
same instant by construction.

> ### ►► THE IMPACT IS THE *PREVIOUS* SHOT'S. IT IS SAID TWICE IN THE CODE. ◄◄
> `item_related` updates only when a round LANDS (`185` `B1`), so at fire time it
> still holds the last one. **PAIR SHOT N's GEOMETRY WITH SHOT N+1's IMPACT.**
> Recorded in the patch, in the host, and here, because **a reader who assumes
> otherwise computes every angle wrong and blames the aim.**

**ONE NEW SYMBOL (`recomp_ge_vr_world_report`, `0x8F000174`) — BUILD TWICE
(`136`). `-NoPoseRec` turns it off with the rest of the recorder.**

---

## §4 — THE RUN THAT ANSWERS IT

**FIRE IN A DELIBERATE PATTERN AND SAY EACH ONE OUT LOUD.** The pattern is the
experiment; a handful of random shots is not.

| # | do this | what it isolates |
|---|---|---|
| **1** | **FORWARD**, level, at a wall ~5 m away. Three shots | the baseline — `215`'s parallel-ray case |
| **2** | **FORWARD**, level, same wall, from ~15 m. Three shots | does the LINEAR miss hold? (`215` §1 predicts YES) |
| **3** | **UP 45 degrees**, three shots | the direction-dependent term |
| **4** | **UP AND RIGHT**, three shots | `[REPORTED]` the worst case |
| **5** | **TURN AROUND 180 and repeat 1** | whether it is tied to facing |

**THE FIRST SHOT OF EACH GROUP CARRIES THE PREVIOUS GROUP'S IMPACT** (§3), so
**three shots per group** means two usable pairs each. **That is why three and
not one.**

**Then `Copy-Item .\gevr.log .\gevr-keep-SHOTWORLD.log` and send it.**

---

## §5 — WHAT IS OWED

1. **BUILD TWICE. RUN §4. SEND THE LOG.**
2. **THE ANGULAR RESIDUAL PER SHOT, COMPUTED OFFLINE**, correlated against
   facing and elevation. **If it is constant in world terms -> one fault. If it
   rotates with facing -> a frame error, and the recording will say which axis.**
3. **THEN `211`'s SOLVER**, built against whatever §2 shows — **and not before**,
   because a solver built for the parallel-ray case alone would leave the
   direction-dependent term untouched and look like a partial failure.

> **AND ONE THING THIS DOES NOT DO:** it does not fix anything. **It is the
> fourth recorder this project has built** (`199` poses, `202` output, `210`
> shots, `216` world) **and the previous three each closed a question that wear
> tests had failed to.**

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
