/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudin <lgaudin@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:44:22 by lgaudin           #+#    #+#             */
/*   Updated: 2023/08/15 14:38:19 by lgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	print_eating(t_philo *ph)
{
	if (!ph->table->has_dead)
		printf(LIGHT_GREEN "%ldms\t%d\tis eating\n" RESET, chrono(ph), ph->id);
}

void	print_dead(t_philo *ph)
{
	printf(LIGHT_RED "%ldms\t%d\tdied\n" RESET, chrono(ph), ph->id);
}

void	print_thinking(t_philo *ph)
{
	if (!ph->table->has_dead)
		printf(BLACK "%ldms\t%d\tis thinking\n" RESET, chrono(ph), ph->id);
}

void	print_sleeping(t_philo *ph)
{
	if (!ph->table->has_dead)
		printf(BLUE "%ldms\t%d\tis sleeping\n" RESET, chrono(ph), ph->id);
}

void	print_forks(t_philo *ph)
{
	if (!ph->table->has_dead)
		printf(BROWN_ORANGE "%ldms\t%d\thas taken a fork\n" RESET, chrono(ph),
			ph->id);
}
