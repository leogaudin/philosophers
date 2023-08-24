/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudin <lgaudin@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:46:48 by lgaudin           #+#    #+#             */
/*   Updated: 2023/08/24 14:31:06 by lgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_usage(void)
{
	printf(LIGHT_RED "Usage: ./philo \
	[number_of_philosophers]\
	[time_to_die]\
	[time_to_eat]\
	[time_to_sleep]\
	[number_of_time_each_philosophers_must_eat]\n" RESET);
	exit(EXIT_FAILURE);
}

void	ft_usleep(int ms)
{
	usleep(ms * 1000);
}
