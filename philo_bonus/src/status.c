/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudin <lgaudin@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:44:22 by lgaudin           #+#    #+#             */
/*   Updated: 2023/08/24 15:38:30 by lgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	print_eating(t_philo *ph)
{
	printf(LIGHT_GREEN "%ld %d is eating\n" RESET, get_time()
		- ph->table->start_time, ph->id);
}

void	print_dead(t_philo *ph)
{
	printf(LIGHT_RED "%ld %d died\n" RESET, get_time() - ph->table->start_time,
		ph->id);
}

void	print_thinking(t_philo *ph)
{
	printf(BLACK "%ld %d is thinking\n" RESET, get_time()
		- ph->table->start_time, ph->id);
}

void	print_sleeping(t_philo *ph)
{
	printf(BLUE "%ld %d is sleeping\n" RESET, get_time()
		- ph->table->start_time, ph->id);
}

void	print_forks(t_philo *ph)
{
	printf(BROWN_ORANGE "%ld %d has taken a fork\n" RESET, get_time()
		- ph->table->start_time, ph->id);
}
