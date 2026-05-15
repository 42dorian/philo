*This project was created as part of the 42 curriculum by dabdulla.*

## Description
The goal of this program is to simulate a circular table of philosophers who alternate between eating, sleeping, and thinking. Each philosopher is represented by a thread, and each fork is protected by a mutex. To eat, a philosopher must successfully pick up both their left and right forks without causing a deadlock or data race.

## Instructions

### Compilation

Navigate to the `philo` directory and use the provided Makefile:

```bash
make
```

### Execution

The program accepts the following arguments:

1. **number_of_philosophers**: The number of philosophers and forks.
2. **time_to_die** (ms): If a philosopher doesn't start eating within this time since their last meal, they die.
3. **time_to_eat** (ms): The time it takes for a philosopher to eat.
4. **time_to_sleep** (ms): The time spent sleeping.
5. **number_of_times_each_philosopher_must_eat** (optional): If all philosophers eat at least this many times, the simulation stops.

**Example Run:**

```bash
./philo 5 800 200 200 7
```

## Resources

### Learning Materials

* [Introduction to Threads](https://www.youtube.com/watch?v=ldJ8WGZVXZk) - Learned how to properly initialize and join threads to ensure parallel execution.
* [Mutexes in C](https://www.youtube.com/watch?v=raLCgPK-Igc) - Gained an understanding of mutual exclusion to prevent data races and manage shared resources.

### AI Usage Disclosure

* **Documentation & Structure:** AI was used to organize the project's README, ensuring all mandatory 42 headers were present and technical sections were clearly categorized for peer reviewers.
* **Synchronization Logic & Timing:** AI helped clarify the necessity of small, strategic delays (like `usleep(500)`) within the simulation. Specifically, it explained how "staggering" the start times of even-numbered philosophers prevents a "deadlock" where everyone grabs their left fork simultaneously.
