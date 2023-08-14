/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudin <lgaudin@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:11:58 by lgaudin           #+#    #+#             */
/*   Updated: 2023/08/14 18:41:35 by lgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

void	end_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
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
