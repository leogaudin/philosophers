/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudin <lgaudin@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:43:47 by lgaudin           #+#    #+#             */
/*   Updated: 2023/08/24 14:14:10 by lgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].eat_count = 0;
		table->philos[i].last_meal = -1;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->nb_philo];
		i++;
	}
}

void	init_table(t_table *table, int ac, char **av)
{
	table->nb_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->has_dead = false;
	if (ac == 6)
		table->nb_eat = ft_atoi(av[5]);
	else
		table->nb_eat = -1;
	table->threads = malloc(sizeof(pthread_t) * table->nb_philo);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
}
