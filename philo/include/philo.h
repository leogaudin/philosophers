/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudin <lgaudin@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:12:03 by lgaudin           #+#    #+#             */
/*   Updated: 2023/08/24 14:32:32 by lgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define BLACK "\033[0;30m"
# define DARK_GRAY "\033[1;30m"
# define RED "\033[0;31m"
# define LIGHT_RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define LIGHT_GREEN "\033[1;32m"
# define BROWN_ORANGE "\033[0;33m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[0;34m"
# define LIGHT_BLUE "\033[1;34m"
# define PURPLE "\033[0;35m"
# define LIGHT_PURPLE "\033[1;35m"
# define CYAN "\033[0;36m"
# define LIGHT_CYAN "\033[1;36m"
# define LIGHT_GRAY "\033[0;37m"
# define RESET "\033[1;37m"

struct	s_table;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
	pthread_t		monitor;
}					t_philo;

typedef struct s_table
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	long			start_time;
	bool			has_dead;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_table;

// actions.c
void				take_forks(t_philo *ph);
void				go_to_sleep(t_philo *ph);
void				leave_forks(t_philo *ph);

// checks.c
bool				did_everyone_eat_enough(t_table *table);
int					ft_atoi(const char *str);
bool				ft_is_valid_atoi(const char *str);
bool				arguments_valid(int argc, char **argv);
void				*check_deaths(void *void_table);

// init.c
void				init_forks(t_table *table);
void				init_philos(t_table *table);
void				init_table(t_table *table, int ac, char **av);

// miscellaneous.c
long				get_time(void);
int					chrono(t_philo *ph);
void				print_usage(void);
void				ft_usleep(int ms);

// status.c
void				print_eating(t_philo *ph);
void				print_dead(t_philo *ph);
void				print_thinking(t_philo *ph);
void				print_sleeping(t_philo *ph);
void				print_forks(t_philo *ph);

#endif
