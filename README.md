*This project has been created as part of the 42 curriculum by jmuth.*

# Philosophers

## Description

The **Philosophers** project is a classic concurrency exercise based on Dijkstra's famous Dining Philosophers problem. It explores the challenges of multi-threaded and multi-process programming: resource sharing, synchronization, and the prevention of deadlocks and data races.

A number of philosophers sit at a round table, alternating between eating, sleeping, and thinking. Each philosopher needs two forks to eat, but there is only one fork between each pair of neighbors. If a philosopher doesn't eat within a given time, they die. The goal is to keep everyone alive as long as possible.

**The project is split into two parts:**

* **Mandatory (threads & mutexes):** Each philosopher is a thread. Forks are protected by mutexes. A supervisor monitors the table and detects deaths or meal completion.
* **Bonus (processes & semaphores):** Each philosopher is a separate process. Forks are managed through a named semaphore acting as a shared counter. Inter-process communication relies on named semaphores for death signaling and meal tracking.

**Key algorithmic choices:**

* **Anti-deadlock:** Even-numbered philosophers pick their left fork first, odd-numbered ones pick their right fork first. In the bonus, an additional semaphore limits concurrent eaters to `nb_philo / 2`.
* **Anti-starvation:** A dynamically calculated thinking delay `(time_to_die - time_to_eat - time_to_sleep) / 2` ensures fair rotation between philosophers, even under tight timing constraints.

## Instructions

### Compilation

Both parts include a comprehensive and secure `Makefile` (relink-free).

* To compile the mandatory part: `cd philo && make`
* To compile the bonus part: `cd philo_bonus && make`
* To clean object files: `make clean`
* To fully clean the project (objects and executable): `make fclean`

### Execution

```bash
./philo <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep> [max_meals]
```

**Arguments:**

* `nb_philo` — Number of philosophers (and forks).
* `time_to_die` (ms) — Time after the start of their last meal before a philosopher dies of starvation.
* `time_to_eat` (ms) — Duration of a meal (requires two forks).
* `time_to_sleep` (ms) — Duration of sleeping after eating.
* `max_meals` (optional) — Simulation stops when every philosopher has eaten this many times.

**Usage examples:**

```bash
./philo 5 800 200 200        # 5 philosophers, runs indefinitely
./philo 5 800 200 200 7      # stops after each philosopher has eaten 7 times
./philo 1 800 200 200        # single philosopher, dies at 800ms
./philo 200 800 200 200 5    # stress test with 200 philosophers
```

The bonus executable is `philo_bonus` and accepts the same arguments.

## Resources

### Classic documentation

To understand and build this project, the following resources are essential:

* **Threads:** `man 3 pthread_create`, `man 3 pthread_join`, `man 3 pthread_mutex_init`
* **Processes (bonus):** `man 2 fork`, `man 2 kill`, `man 2 waitpid`
* **Semaphores (bonus):** `man 3 sem_open`, `man 3 sem_wait`, `man 3 sem_post`, `man 3 sem_close`, `man 3 sem_unlink`
* **Time:** `man 2 gettimeofday`, `man 3 usleep`

### Community resources

* **CodeVault (YouTube):** Excellent video series on UNIX threads, mutexes, and the dining philosophers problem. Invaluable for visualizing thread lifecycle and understanding mutex mechanics.
* **Philosophers visualizer tools:** Used third-party log analyzers to verify timing accuracy and detect edge-case starvation scenarios.

### Artificial Intelligence usage

During this project, an AI (Claude) was used as an aid for the following tasks:

* **README:** Definition of the structure, error correction, and help with English wording.