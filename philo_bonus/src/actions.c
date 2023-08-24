/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudin <lgaudin@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:46:13 by lgaudin           #+#    #+#             */
/*   Updated: 2023/08/24 15:02:31 by lgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	take_forks(t_philo *ph)
{
	sem_wait(ph->table->forks);
	print_forks(ph);
	sem_wait(ph->table->forks);
	print_forks(ph);
}

void	go_to_sleep(t_philo *ph)
{
	ph->eat_count++;
	print_sleeping(ph);
	ft_usleep(ph->table->time_to_sleep);
}

void	leave_forks(t_philo *ph)
{
	sem_post(ph->table->forks);
	sem_post(ph->table->forks);
	go_to_sleep(ph);
}
