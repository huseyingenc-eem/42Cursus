*This project has been created as part of the 42 curriculum by hgenc.*

# Philosophers

## Description

**Philosophers** is a concurrent programming exercise built around the classic *Dining Philosophers* problem, first formulated by Edsger Dijkstra in 1965. It is a hands-on introduction to threads, mutexes, and the real-world pitfalls of shared-state concurrency — deadlocks, race conditions, and starvation.

A number of philosophers sit around a round table with a bowl of spaghetti in the middle. Between each pair of neighbors lies a single fork, so the table has exactly as many forks as philosophers. A philosopher alternates between three states: **thinking**, **eating**, and **sleeping**. To eat, they must pick up both the fork on their left and the fork on their right. If a philosopher does not start a new meal within `time_to_die` milliseconds of their previous one, they starve and the simulation ends.

The program models each philosopher as an independent thread and each fork as a mutex, with no global variables, no memory leaks, and no data races.

## Instructions

### Clone

```sh
git clone git@vogsphere.42kocaeli.com.tr:vogsphere/intra-uuid-8d206b78-2d40-4a22-98ec-20807e6a3699-7102467-hgenc philo
cd philo
```

### Build

```sh
make        # build the philo binary
make clean  # remove object files
make fclean # remove object files and the binary
make re     # fclean + all
```

The project is compiled with `-Wall -Wextra -Werror -pthread` using `cc`.

### Run

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Unit | Description |
|----------|------|-------------|
| `number_of_philosophers` | count | Number of philosophers and forks at the table. |
| `time_to_die` | ms | A philosopher dies if they don't start eating within this window of their last meal (or the simulation start). |
| `time_to_eat` | ms | Time a philosopher spends eating while holding both forks. |
| `time_to_sleep` | ms | Time a philosopher spends sleeping after a meal. |
| `number_of_times_each_philosopher_must_eat` | count (optional) | If every philosopher has eaten at least this many times, the simulation stops. |

### Examples

```sh
./philo 5 800 200 200           # classic stable configuration
./philo 4 410 200 200           # tight timing — philosophers on the edge
./philo 5 800 200 200 7         # stops once every philosopher has eaten 7 times
./philo 1 800 200 200           # lone philosopher — dies after time_to_die
```

### Output format

Each state change is printed as `timestamp_in_ms X action`:

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
...
810 3 died
```

## Resources

References consulted while working on this project:

- Dijkstra, E. W. — *Hierarchical ordering of sequential processes* (EWD310) — original dining philosophers formulation.
  https://www.cs.utexas.edu/users/EWD/transcriptions/EWD03xx/EWD310.html
- Chandy, K. M. & Misra, J. — *The Drinking Philosophers Problem* — ACM TOPLAS, 1984.
  https://dl.acm.org/doi/pdf/10.1145/1780.1804
- Sidney, S. — *Dining philosophers revisited* — ACM SIGCSE Bulletin, 1990.
  https://dl.acm.org/doi/pdf/10.1145/101085.101091
- POSIX Threads Programming — LLNL tutorial.
  https://hpc-tutorials.llnl.gov/posix/
- PRISM — *The dining philosophers* (model-checking tutorial).
  https://www.prismmodelchecker.org/tutorial/phil.php
- Philosophers Project 42 — reference walkthrough.
  https://philo.yaajagro.tech/

### AI usage

I used AI purely as a tool in this project. I turned to it for ideas when I got stuck debugging on my own, and later to explain a few details I did not fully understand. All the code was written by me and I can walk through every line of it.
