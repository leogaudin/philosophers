/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudin <lgaudin@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:45:12 by lgaudin           #+#    #+#             */
/*   Updated: 2023/08/24 16:03:08 by lgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

bool	did_everyone_eat_enough(t_table *table)
{
	int	i;

	i = 0;
	if (table->nb_eat == -1)
		return (false);
	while (i < table->nb_philo)
	{
		if (table->philos[i].eat_count < table->nb_eat)
			return (false);
		i++;
	}
	return (true);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	negative;
	int	result;

	i = 0;
	negative = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		negative *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	result *= negative;
	return (result);
}

bool	ft_is_valid_atoi(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '\0')
		return (true);
	else
		return (false);
}

bool	arguments_valid(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (false);
	while (i < argc)
	{
		if (!ft_is_valid_atoi(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

void	*check_deaths(void *void_table)
{
	t_philo	*philo;

	philo = (t_philo *)void_table;
	while (1)
	{
		if (get_time() - philo->last_meal > philo->table->time_to_die
			&& philo->last_meal != -1
			&& (philo->eat_count < philo->table->nb_eat
				|| philo->table->nb_eat == -1))
		{
			print_dead(philo);
			philo->table->has_dead = true;
			kill_everyone(philo->table, philo->id);
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
