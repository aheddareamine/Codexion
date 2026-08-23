*This project has been created as part of the 42 curriculum by aaheddar.*

# Codexion

## Description

Codexion is a small concurrency simulation written in C. A group of coders sit around a shared
table and each one keeps cycling through three phases: compiling, debugging, then refactoring.
To compile they need two USB dongles at the same time, one on their left and one on their right,
and there are exactly as many dongles as coders. So neighbours are always fighting over the same
dongle, and the whole thing is really the dining philosophers problem wearing a different costume.

On top of the classic problem the subject adds a few twists. A dongle can't be picked up again
straight after it's released — it has a cooldown first. When several coders want the same dongle
the tie is broken by a scheduler, either FIFO (whoever asked first) or EDF (whoever is closest to
burning out). And a coder burns out if it goes too long without starting a new compile, which ends
the simulation.

Every coder runs in its own thread. A separate monitor thread watches for burnouts and for the
moment everyone has compiled enough. The program stops either when a coder burns out or when every
coder has compiled at least the required number of times.

## Instructions

Build it with make:

```
make        # builds ./codexion
make clean  # removes object files
make fclean # removes objects and the binary
make re     # fclean + build
```

Everything compiles with `cc -Wall -Wextra -Werror -pthread`.

Run it with eight arguments, all required:

```
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug \
           time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

- `number_of_coders`: how many coders, and also how many dongles.
- `time_to_burnout`: ms; if a coder doesn't start a compile within this long of its last
  compile start (or the sim start), it burns out.
- `time_to_compile`: ms spent compiling, holding both dongles.
- `time_to_debug`: ms spent debugging.
- `time_to_refactor`: ms spent refactoring, after which it tries to compile again.
- `number_of_compiles_required`: once every coder has compiled at least this many times, the
  sim stops.
- `dongle_cooldown`: ms a dongle stays unavailable after being put down.
- `scheduler`: `fifo` or `edf`, exactly one of those two words.

Times are milliseconds. The arguments are validated: negative values, non-integers, and any
scheduler that isn't `fifo` or `edf` are rejected.

A couple of examples:

```
./codexion 5 800 200 200 200 5 60 fifo
./codexion 3 400 100 100 100 10 30 edf
```

Each line of output looks like `timestamp_in_ms coder_number message`, for example
`201 1 is debugging`. The messages are "has taken a dongle", "is compiling", "is debugging",
"is refactoring", and "burned out". A compile is always preceded by that coder taking two
dongles, and if a coder burns out that line is the last thing printed.

## Blocking cases handled

Deadlock. The dangerous case is every coder grabbing its left dongle and then waiting forever for
its right one a circular wait, which is one of Coffman's four conditions for deadlock (along with
mutual exclusion, hold-and-wait, and no preemption). I break the circular wait by ordering the
resources: a coder always takes the lower-numbered of its two dongles first, then the higher one.
With that rule a cycle can't form, because there's always at least one coder holding the
highest-numbered dongle in any contested group, and that coder isn't waiting on anything below it.
Hold-and-wait still happens, but breaking a single Coffman condition is enough. On the mutex side I
also never hold two dongle locks at once, so there's no separate lock-ordering deadlock.

Starvation. When several coders want the same dongle, a per-dongle priority queue decides who gets
it next. Under `fifo` that's arrival order. Under `edf` it's the coder with the earliest burnout
deadline (`last_compile_start + time_to_burnout`), with the request's arrival order as a
deterministic tie-breaker for the rare equal-deadline case. EDF is what keeps a coder that's close
to burning out from being passed over, which is how the simulation stays alive when the parameters
allow it.

Cooldown. Releasing a dongle stamps it with `available_at = now + dongle_cooldown`. A coder that
finds the dongle free but still cooling down doesn't spin it waits with a timed wait until
exactly that moment, then rechecks.

Precise burnout detection. The monitor thread polls every 0.5 ms, so the gap between an actual
burnout and the monitor noticing it is at most one poll, comfortably inside the 10 ms the subject
allows. A coder that has already met its compile quota is exempt from the burnout check, since it
has finished rather than stalled.

Log serialization. All output goes through a single lock and one `write` call per line, so two
messages can never end up mixed on the same line. The same lock is used for the end-of-simulation
check, which is what guarantees no ordinary state message can slip out after the burnout line.

## Thread synchronization mechanisms

The program uses POSIX mutexes and condition variables. There are no global variables; every
thread reaches shared state through pointers (each coder holds a pointer back to the shared
simulation, and to its two dongles).

Each dongle has its own `pthread_mutex_t` guarding its state whether it's taken, its cooldown
timestamp, and its waiting queue plus a `pthread_cond_t` that waiters block on. A coder acquires
a dongle by locking it, putting a request into the queue, and waiting on the condition variable
until three things are true at once: the dongle is free, its cooldown has passed, and its own
request is at the front of the scheduler's queue. On release the dongle is marked free and every
waiter is broadcast awake to re-check. Waiting on the condition variable instead of looping means
a blocked coder uses no CPU, and the loop re-tests its condition on every wake so spurious wakeups
are harmless.

Logging is protected by a dedicated mutex. A coder only prints while holding it, and the print
function also checks the end flag under that same lock and stays silent once the sim has ended.

Communication between the coders and the monitor is the delicate part, and it's handled with two
more pieces. First, each coder has its own mutex protecting the two fields the monitor needs to
read from another thread: the timestamp of its last compile and its compile count. The coder locks
it when it writes those; the monitor locks it when it reads them. Without that lock the monitor
could read a half-updated timestamp and either miss a real burnout or invent a fake one.

Second, the end of the simulation is a small custom event built from a flag and a mutex. Only the
monitor sets it — when a coder burns out, or when everyone has met the quota. Setting it isn't
enough on its own, though: coders can be parked on a dongle condition variable at that moment,
possibly one a burned-out coder will never release, and they'd wait forever. So ending the run
also broadcasts every dongle's condition variable, which wakes those parked coders; their
acquisition loop checks the end flag first and abandons the wait, so every thread becomes joinable
and the program exits cleanly.

A few concrete race conditions and how they're avoided:

- The monitor reading a coder's last-compile time while the coder is updating it prevented by
  the per-coder mutex around both the read and the write.
- A state line printing after the burnout line prevented because the print function's end-check
  and its write share the log mutex with the monitor's set-end-and-print-burnout, so the two can't
  interleave.
- The scheduler comparing a coder's live burnout deadline while that coder changes it — avoided by
  snapshotting the deadline into the request when it's queued, so the priority queue never touches
  another coder's live state.

## Resources

- The POSIX threads manual pages: `pthread_create`, `pthread_join`, `pthread_mutex_lock`,
  `pthread_cond_wait`, `pthread_cond_timedwait`, `pthread_cond_broadcast`, and the related calls.
- The dining philosophers problem, as the classic framing of this exact resource-sharing setup.
- Coffman's four conditions for deadlock, used to reason about why resource ordering is enough to
  prevent it.
- Standard material on the binary heap / priority queue, which the FIFO and EDF arbitration is
  built on (implemented by hand, since the standard library one isn't allowed).

How AI was used: I used an AI assistant (Claude) as a tutor and reviewer rather than to hand me
finished code. It helped me talk through the concurrency design the deadlock argument, the
condition-variable waiting protocol, and the clean-shutdown problem explained the parts I wasn't
sure about, helped scaffold and review some of the implementation, and drafted parts of this
documentation. I read, tested, and reworked everything myself, and I understand and take
responsibility for all of the code. (Edit this to match exactly how you worked before submitting.)