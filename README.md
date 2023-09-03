<div align="center">
	<img src="./assets/banner.webp">
	<p>
		<b><i>"Arrêtez de vous disputer, c'est puéril, on dirait des puéricultrices"</i></b>
		<br />
		<i>Marc-Aurèle</i>
	</p>
	<h1>🧔🏻‍♂️ Philosophers</h1>
	<p>In this project, you will learn the basics of threading a process. You will see how to create threads and you will discover mutexes.</p>
	<a href="https://wakatime.com/badge/user/db0e5671-cec5-4e7b-9d41-19a881e67f7d/project/1f68e433-12de-44a7-a9ef-3fe6ed0302c2">
		<img src="https://wakatime.com/badge/user/db0e5671-cec5-4e7b-9d41-19a881e67f7d/project/1f68e433-12de-44a7-a9ef-3fe6ed0302c2.svg" alt="wakatime">
	</a>
	<br />
	<img src="https://img.shields.io/badge/norminette-passing-success"/>
	<a href="https://developer.apple.com/library/archive/documentation/Performance/Conceptual/ManagingMemory/Articles/FindingLeaks.html">
		<img src="https://img.shields.io/badge/leaks-none-success" />
	</a>
	<img src="https://img.shields.io/badge/bonus-included-success"/>
	<br />
	<img src="https://img.shields.io/badge/125%2F100-success?logo=42&logoColor=fff" />
</div>

## 📖 Table of Contents
<!--ts-->
   * [⚙️ Usage](#usage)
   * [🤔 How Does Philosophers Work?](#how-does-philosophers-work)
	  * [🧵 Threads](#threads)
	  * [🔒 Mutexes](#mutexes)
	  * [🍽️ The Dining Philosophers Problem](#the-dining-philosophers-problem)
	  * [💭 States](#states)
		 * [🍝 Eating](#eating)
		 * [🧐 Thinking](#thinking)
		 * [😴 Sleeping](#sleeping)
	  * [🛠️ Functions](#functions)
	   	* [`start_simulation`](#start_simulation)
		* [`take_forks`](#take_forks)
		* [`leave_forks`](#leave_forks)
		* [`routine`](#routine)
	  * [🌟 Bonus](#bonus)
	    * [🔢 Semaphores](#semaphores)
   * [🙏🏼 Credits](#credits)
<!--te-->

## Usage

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_time_each_philosophers_must_eat]
```

## How Does Philosophers Work?

Philosophers is a quite simple project by itself, but it relies on brand new concepts at the time you have to do it: ****threads and mutexes****.

### Threads

A thread is a sequence of instructions that can be executed independently of other code. This means that a program can do many things at the same time. This is called concurrency.

### Mutexes

A mutex is a lock that we can use to prevent two threads from accessing the same resource at the same time. This is useful when we have a shared resource that we want to protect from being modified by two threads at the same time.

### The Dining Philosophers Problem

* $x$ number of silent philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers.

* Anytime they can, philosophers will eat.

* To do so, they need to take a fork on their left and on their right.

The situation would be pretty simple if there was $x \times 2$ forks available, but unfortunately, there are only $x$ forks available.

* A philosopher can only eat if they have both of their forks.

* The whole complexity of the problem stands in the fact that we need to represent the forks as a shared resource that is alternately **available or not**.

* That is where **mutexes** come in handy.

> 💡 Each philosopher is represented by a thread, and each fork is represented by a mutex.

### States

A philosopher can be in one of the following states:

- **Eating**: The philosopher is eating.
- **Sleeping**: The philosopher is sleeping.
- **Thinking**: The philosopher is thinking.
- **Dead**: The philosopher is dead.

#### Eating

When a philosopher is eating, they are using both of their forks.

The two corresponding mutexes are locked.

#### Thinking

When a philosopher is "thinking", they are waiting for one or two forks to be available.

#### Sleeping

When a philosopher is sleeping, they are not using any forks.

## Functions
#### `start_simulation`

```C
void	start_simulation(t_table *table)
{
	int	i;

	table->start_time = get_time();
	if (table->nb_philo == 1)
	{
		print_thinking(&table->philos[0]);
		usleep(table->time_to_die * 1000);
		print_dead(&table->philos[0]);
		return ;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_create(&table->threads[i], NULL, &routine, &table->philos[i]);
		i++;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->threads[i], NULL);
		i++;
	}
}
```

This function is only about launching the different threads and waiting for them to finish, nothing more (except handling the edge case of an alone philosopher).

#### `take_forks`

```C
void	take_forks(t_philo *ph)
{
	pthread_mutex_lock(ph->left_fork);
	print_forks(ph);
	pthread_mutex_lock(ph->right_fork);
	print_forks(ph);
}
```

This function represent a philosopher taking the forks on their left and right.

Luckily, we can use the `pthread_mutex_lock` function to lock a mutex, and wait for it to be available.

A whole lot of abstraction is done by the function, we just have to call it.

> Actually no, this version would cause deadlocks for a low number of philosophers and low latency between the actions, so you will have to find a way to prevent that, or look inside the code if you're lazy and don't care about getting −42.


#### `leave_forks`

```C
void	leave_forks(t_philo *ph)
{
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	go_to_sleep(ph);
}
```

Again, this function is pretty simple, it just unlocks the mutexes that were locked by the `take_forks` function, and then the philosopher goes to sleep.

#### `routine`

```C
void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (!ph->table->has_dead && !did_everyone_eat_enough(ph->table))
	{
		if (get_time() - ph->last_meal > ph->table->time_to_die)
		{
			ph->table->has_dead = true;
			print_dead(ph);
			return (NULL);
		}
		print_thinking(ph);
		take_forks(ph);
		ph->last_meal = get_time();
		print_eating(ph);
		usleep(ph->table->time_to_eat * 1000);
		leave_forks(ph);
	}
	return (NULL);
}
```

The `routine` function is the one that is called by each thread.

It is a loop that will run until a philosopher dies on the table (good dinner) or until they have eaten enough.

During this loop, if he's not dead, the philosopher will try to take the forks, update its last meal time, eat for `time_to_eat` milliseconds, and then leave the forks and go to sleep for `time_to_sleep` milliseconds.

### Bonus

The bonus part introduces additional requirements:

> *All the forks are put in the middle of the table.*
>
> *They have no states in memory but the number of available forks is represented by a semaphore.*
>
> *Each philosopher should be a process. But the main process should not be a philosopher.*

Basically, it only needs the following transformations:

* **Philosophers**: threads → **processes**
* **Forks**: mutexes → **semaphores**

#### Processes

The current version of this repository does not include the transition from threads to processes yet.

#### Semaphores

A semaphore is pretty much a computer representation of a counter, with additional particularities:

* `sem_open`, this method creates a new semaphore, with a name, a mode, permissions, and an initial value

* `sem_wait`, this method:

	1. **Locks** the counter (like *"hey, I reserved it, let me just do some things and after that I'll decrement it"*)
	2. **Executes** the critical actions, similarly to the ones executed between `pthread_mutex_lock` and `pthread_mutex_unlock`.
	3. **Decrements** the counter

* `sem_post`, which simply increments the counter

* `sem_unlink`, which unlinks (surprising) the name reserved and the semaphore

* `sem_close`, which deletes and does all the freeing job on the semaphore

Therefore, the bonus requirements of the subject are perfectly met by the concept of semaphores:

* There is no concept of left or right fork, they can just be represented by **a counter of forks available to everyone**.
* The **locking part** that we benefited from mutexes is still provided.

## Credits

*🙇🏻‍♂️ The playlist from CodeVault is super useful and can make you go from "how the hell does this work" to "okay let's go this is fire".*

[Link to the playlist](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
