*This project has been created as part of the 42 curriculum by luimarti*

# Philosophers

## Description

Philosophers is an implementation of the dining philosophers problem, the
classic exercise in concurrent programming formulated by Dijkstra in 1965.

A number of philosophers sit around a table. Each one alternates between
thinking, eating and sleeping, and needs the two forks next to them in order to
eat — which means competing with their neighbours for a shared resource. The
simulation must run without a philosopher ever starving, and must report the
exact moment one dies if it happens.

The project is an introduction to threads and mutexes. Each philosopher runs in
its own thread, and each fork is protected by a mutex. The difficulty is not
writing the logic but making it correct under concurrency: the naive solution
where everyone picks up their left fork first deadlocks immediately, two threads
writing to the terminal at the same time interleave their output, and a
philosopher's death has to be detected within milliseconds without introducing a
race on the timestamps. Every shared piece of state has to be protected, and no
thread may be left unjoined.

Correctness here is not something you can prove by running it once — the whole
point is that a program can appear to work for minutes and still contain a race.

## Instructions

```bash
git clone https://github.com/Lucho-cadete/Philosophers.git
cd Philosophers
make
```

Run it with four or five arguments, all in milliseconds except the first and
the last:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Meaning |
|---|---|
| `number_of_philosophers` | How many philosophers, and therefore how many forks |
| `time_to_die` | Milliseconds since the last meal after which a philosopher dies |
| `time_to_eat` | Milliseconds a meal takes (both forks held for this long) |
| `time_to_sleep` | Milliseconds a philosopher sleeps after eating |
| `number_of_times_each_philosopher_must_eat` | Optional; the simulation stops when every philosopher has eaten this many times |

Examples:

```bash
./philo 5 800 200 200        # runs indefinitely, nobody should die
./philo 5 800 200 200 7      # stops once each philosopher has eaten 7 times
./philo 4 410 200 200        # tight timing, no death expected
./philo 1 800 200 200        # a single philosopher cannot eat: must die
./philo 4 310 200 100        # a death is expected here
```

Every state change is printed as `timestamp_in_ms philosopher_id action`, and a
death is announced within 10 ms of occurring.

## Technical choices

<!-- TODO: this is what gets discussed in the evaluation. Describe how you
     avoided the deadlock (odd/even philosophers picking forks in opposite
     order? a delay for even-numbered ones?), how the monitoring of deaths is
     done (a dedicated thread? polling interval?), and how you protect the
     timestamps and the printing so output never interleaves. -->

## Resources

- [Dijkstra, *EWD-310: Hierarchical Ordering of Sequential Processes*](https://www.cs.utexas.edu/~EWD/transcriptions/EWD03xx/EWD310.html)
  — the original formulation of the problem.
- `man 3 pthread_create`, `man 3 pthread_mutex_lock`, `man 2 gettimeofday` —
  the entire API this project uses fits in these pages.
- [The Linux Programming Interface](https://man7.org/tlpi/), chapters 29–30 —
  threads and thread synchronisation.
- [Valgrind / Helgrind](https://valgrind.org/docs/manual/hg-manual.html) — the
  tool that finds the races a normal run will not show you.

### Use of AI

AI assistance was used for: understanding what a thread is and how it differs
from a process, which was new to me; explaining what a race condition is and why
a program can be wrong even when it runs correctly every time I try it;
clarifying why the naive fork-picking order deadlocks and what the usual
strategies against it are; and reviewing my monitoring loop for the case where a
philosopher dies while holding a fork. The implementation, the synchronisation
design and the debugging are mine.
