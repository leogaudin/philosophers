/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudin <lgaudin@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:11:58 by lgaudin           #+#    #+#             */
/*   Updated: 2023/08/22 14:20:32 by lgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"
#include <sys/wait.h>

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while ((ph->eat_count < ph->table->nb_eat || ph->table->nb_eat == -1)
		&& !ph->table->has_dead)
	{
		print_thinking(ph);
		take_forks(ph);
		if (get_time() - ph->last_meal > ph->table->time_to_die)
		{
			ph->table->has_dead = true;
			print_dead(ph);
			exit(EXIT_FAILURE);
		}
		ph->last_meal = get_time();
		print_eating(ph);
		usleep(ph->table->time_to_eat * 1000);
		leave_forks(ph);
	}
	exit(EXIT_SUCCESS);
	return (NULL);
}

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
		table->pid[i] = fork();
		if (table->pid[i] == 0)
			routine(&table->philos[i]);
		i++;
	}
	while (1)
	{
		check_death(table);
		exit(EXIT_FAILURE);
	}
	i = 0;
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
	free(table->threads);
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
