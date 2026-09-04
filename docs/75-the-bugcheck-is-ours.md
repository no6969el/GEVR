# 75 — THE MACHINE BUGCHECK IS OURS. `39`'s "not our bug" is RETRACTED.

**2026-08-23, ~16:00. Read from the Windows event log and the app fault log on
the machine itself, not inferred.**

---

## `39` SAID THIS, AND IT IS WRONG

> *"The machine crash on 2026-08-23 ... No user-mode process can do that.
> Memory-training / EXPO instability at firmware level. Re-test memory stability
> before attributing any future machine-level fault to this project."*

**That paragraph sent the owner of this machine to lower his RAM speed. He did.
It crashed again.** Three more times, two of them inside the session that is
reading this.

## THE EVIDENCE

```
Bugcheck 0x139  KERNEL_SECURITY_CHECK_FAILURE   arg1 = 0x3
  2026-08-22 23:48
  2026-08-23 01:24
  2026-08-23 15:11     <- follows the 15:05 worn session
  2026-08-23 15:46     <- follows the -UnitsPerMetre 50 run
  2026-08-23 15:56     <- follows the -UnitsPerMetre 400 run
```

**Same bugcheck, same parameters, five times.** `0x139` with `arg1 = 3` is
**LIST_ENTRY corruption** caught by the kernel's own integrity check.

**And in the Application log, the same binary, over and over:**

```
GoldenRecomp.exe  faulting module nvwgf2umx.dll   0xc0000005   (NVIDIA D3D12 UMD)
GoldenRecomp.exe  faulting module D3D12Core.dll   0xc0000005
```

**We are access-violating INSIDE the graphics driver.**

## WHY A USER-MODE PROCESS CAN, IN FACT, DO THIS

`39`'s claim is true of ordinary user-mode memory and **false for the graphics
stack.** A process that hands D3D12 a freed resource — or frees one the GPU is
still reading — corrupts driver-side bookkeeping that lives partly in the
kernel. **The user-mode driver AVs, and if it happens with work in flight the
kernel side takes the list corruption and bugchecks.**

**That is precisely the defect this project already has on the board:**

- **O21**: teardown can free GPU resources mid-use; `WaitForSingleObject(...,
  1000)`'s result is discarded and `shutdown: gpu idle` is logged
  unconditionally.
- **`64`**: the teardown crash, 100% reproducible,
  `PresentQueue::threadPresent` -> `VIRenderer::render` -> `setSRV`.
- **`64` again**: `teardown: present thread drained` **prints and is false.**

**A false "drained" is exactly the shape that produces a use-after-free at
shutdown.**

## THE LOGS CLOSE THE LOOP — XR sessions die, non-XR sessions do not

| Run | Teardown output | Machine |
|---|---|---|
| `-NoXr`, level played, quit (`73`) | **both lines printed, clean** | **survived** |
| worn, 15:05 | both lines printed | **bugcheck at ~15:04** |
| `-UnitsPerMetre 50` | **NONE. The log stops mid-line** | **bugcheck** |
| `-UnitsPerMetre 400` | **NONE. The log stops mid-line** | **bugcheck** |

**Two of the three XR logs end without our shutdown getting a single line out.**
The machine died before or during teardown.

## WHAT TO DO ABOUT IT, IN ORDER

1. **STOP CLOSING VR SESSIONS WITH THE X.** Kill the process instead
   (`taskkill /F /IM GoldenRecomp.exe`) until teardown is fixed. **This is also
   the experiment:** a force-kill runs none of our shutdown code. **If
   force-killing never bugchecks, O21 is proven, not suspected.**
2. **Then fix O21 properly** — honour the fence wait's result, and make
   `present thread drained` true or delete it.
3. **`18` asked "is the X as safe as taskbar-close?"** and was never answered.
   It is now urgent and it is the same question.

## FIRST RESULT OF THE FORCE-KILL EXPERIMENT — n=1, and it points the right way

**2026-08-23 16:06.** The `-UnitsPerMetre 25` session was ended with
`taskkill /F /IM GoldenRecomp.exe` instead of the X. **The machine survived.**
Ten minutes later it was still up, with no bugcheck logged.

**That is the first VR session today that did not take the machine down**, and it
is the one that ran **none of our shutdown code**.

**n=1. It is not proof.** What would make it proof: three more force-kills with
no bugcheck, and one deliberate X-close that produces one. **The X-close half of
that experiment costs the user a reboot each time, so it is run last, once, and
only when he agrees to it.**

## THE FORCE-KILL IS NOT A FIX, AND THIS MUST NOT BE FORGOTTEN

**Raised by the user, 2026-08-23, and it is the right frame:**

> *"We need to be able to close this game gracefully, as a tester closing it
> normally."*

**Nobody who is handed this build will know to run `taskkill`.** They will click
the X, which is the only exit a person has any reason to use — and today that
takes the whole machine down. **The workaround protects THIS session's testing;
it protects no user at all.**

**That is B4 on the board, and it is ship-blocking in a way B3 alone is not.**
A crash on exit that costs a reboot is not a rough edge; it is the last thing
anyone experiences of the software.

## THE RULE THIS EARNS, AND IT IS THE EXPENSIVE KIND

**"No user-mode process can do that" is an argument from a mental model of an
API boundary, and it was used to close an investigation.**

`48` already says measure rather than describe, and `70` says *when an
instrument and a picture disagree, go and look from outside.* **This adds:
before writing off a fault as somebody else's, check whether the fault's TIMING
belongs to you.** Five bugchecks, every one within a minute of a VR session
ending, and a `-NoXr` session that never did it. **The timing was in the event
log the whole time and nobody opened it.**
