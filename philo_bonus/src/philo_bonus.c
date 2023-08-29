/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudin <lgaudin@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:11:58 by lgaudin           #+#    #+#             */
/*   Updated: 2023/08/29 10:01:04 by lgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"
#include <sys/wait.h>

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph->last_meal = get_time();
	pthread_create(&ph->monitor, NULL, &check_deaths, ph);
	pthread_detach(ph->monitor);
	if (ph->id % 2 == 0)
		ft_usleep(1);
	while ((ph->eat_count < ph->table->nb_eat || ph->table->nb_eat == -1)
		&& !ph->table->has_dead)
	{
		print_thinking(ph);
		take_forks(ph);
		print_eating(ph);
		ph->last_meal = get_time();
		ft_usleep(ph->table->time_to_eat);
		leave_forks(ph);
	}
	exit(EXIT_SUCCESS);
	return (NULL);
}

void	one_philo(t_table *table)
{
	print_thinking(&table->philos[0]);
	ft_usleep(table->time_to_die);
	print_dead(&table->philos[0]);
}

void	start_simulation(t_table *table)
{
	int	i;

	table->start_time = get_time();
	if (table->nb_philo == 1)
		return (one_philo(table));
	i = 0;
	while (i < table->nb_philo)
	{
		table->pid[i] = fork();
		if (table->pid[i] == 0)
			routine(&table->philos[i]);
		i++;
	}
	waitpid(-1, 0, 0);
}

void	end_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		sem_unlink("forks");
		sem_close(table->forks);
		i++;
	}
	free(table->philos);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!arguments_valid(argc, argv))
		print_usage();
	init_table(&table, argc, argv);
	init_philos(&table);
	init_forks(&table);
	start_simulation(&table);
	end_simulation(&table);
	return (0);
}
