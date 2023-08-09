/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 06:29:28 by loandrad          #+#    #+#             */
/*   Updated: 2023/08/04 18:20:08 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

# define HLP_MSG "\n--- TO RUN PROGRAM ---\n\
./philo num_philos time(to die) time(to eat) time(to sleep)\
 [times(each philo eats)]\n\nExample1 : ./philo 5 900 200 200 3\n\
Example2 : ./philo 5 900 200 200\n\n------ NOTE ------\nNote1    : \
[times(each philo eats)] is optional\nNote2    : \
time is denoted in milliseconds (1000 ms = 1 second)\nNote3    : \
all arguments should be greater than zero\n\n"

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock;
	int				ph_num;
	int				id;
	int				l_fork;
	int				r_fork;
	int				meal_num;
	int				*ate;
	int				*dead;
	int				total_meals;
	long long		start;
	long long		last_meal;
	long long		eat_timer;
	long long		die_timer;
	long long		slp_timer;
}	t_philo;

// Arguments
int			arg_atoi(char *nb);
int			arg_check(int argc, char *argv[], t_philo **ph);

// Initialization
int			init_philos(int argc, char *argv[], t_philo *ph);
int			init_mutexes(t_philo *ph);
int			make_threads(t_philo *ph, int ph_num);
int			init_prog(int argc, char *argv[], t_philo **ph);

// Program functions
long long	get_time(void);
void		*routine(void *arg);
void		slp_pause(long long msec);
void		join_threads(t_philo *ph);
void		free_exit(t_philo *ph, int code);

#endif