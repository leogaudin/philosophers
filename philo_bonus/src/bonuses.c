/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudin <lgaudin@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:19:53 by lgaudin           #+#    #+#             */
/*   Updated: 2023/08/22 14:20:08 by lgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"
#include <sys/wait.h>

void	kill_everyone(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		kill(table->pid[i], SIGKILL);
		i++;
	}
}

void	check_death(t_table *table)
{
	int	status;

	waitpid(-1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		kill_everyone(table);
}
