/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudin <lgaudin@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:19:53 by lgaudin           #+#    #+#             */
/*   Updated: 2023/08/24 16:02:29 by lgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"
#include <sys/wait.h>

void	kill_everyone(t_table *table, int sender)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (sender != i)
			kill(table->pid[i], SIGKILL);
		i++;
	}
}
