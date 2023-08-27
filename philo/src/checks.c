/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudin <lgaudin@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:45:12 by lgaudin           #+#    #+#             */
/*   Updated: 2023/08/27 13:14:44 by lgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	if (str[i] == '-')
		return (false);
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
	int		i;
	t_table	*table;

	i = 0;
	table = (t_table *)void_table;
	while (1)
	{
		if (did_everyone_eat_enough(table))
			break ;
		if (get_time() - table->philos[i].last_meal > table->time_to_die
			&& table->philos[i].last_meal != -1
			&& (table->philos[i].eat_count < table->nb_eat
				|| table->nb_eat == -1))
		{
			print_dead(&table->philos[i]);
			table->has_dead = true;
			exit(EXIT_FAILURE);
		}
		i = (i + 1) % table->nb_philo;
	}
	return (0);
}
