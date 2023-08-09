/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 06:27:45 by loandrad          #+#    #+#             */
/*   Updated: 2023/08/04 15:45:58 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_philo *ph)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(ph->lock, NULL) != 0)
		return (-1);
	while (i < ph->ph_num)
	{
		if (pthread_mutex_init(&ph->forks[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

static void	init_time(char *argv[], t_philo *ph)
{
	long long	start;

	start = 0;
	if (start == 0)
		start = get_time();
	ph->start = start;
	ph->last_meal = start;
	ph->eat_timer = arg_atoi(argv[3]);
	ph->die_timer = arg_atoi(argv[2]);
	ph->slp_timer = arg_atoi(argv[4]);
}

static void	init_values(int index, t_philo *ph)
{
	ph->id = index + 1;
	ph->l_fork = index;
	ph->r_fork = (index + 1) % ph->ph_num;
	ph->meal_num = 0;
	ph->total_meals = 0;
}

static int	take_input(t_philo *ph)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock;
	int				*dead;
	int				*ate;

	forks = malloc(sizeof(pthread_mutex_t) * ph->ph_num);
	lock = malloc(sizeof(pthread_mutex_t));
	dead = malloc(sizeof(int));
	ate = malloc(sizeof(int));
	if (!forks || !dead || !lock || !ate)
		return (-1);
	*dead = 0;
	*ate = 0;
	ph->ate = ate;
	ph->forks = forks;
	ph->dead = dead;
	ph->lock = lock;
	return (0);
}

int	init_philos(int argc, char *argv[], t_philo *ph)
{
	int				i;
	int				ph_num;

	i = 0;
	ph_num = arg_atoi(argv[1]);
	ph->ph_num = ph_num;
	if (take_input(ph) != 0)
		return (-1);
	while (i < ph_num)
	{
		ph[i].forks = ph[0].forks;
		ph[i].lock = ph[0].lock;
		ph[i].dead = ph[0].dead;
		ph[i].ate = ph[0].ate;
		ph[i].ph_num = ph_num;
		init_time(argv, &ph[i]);
		init_values(i, &ph[i]);
		if (argc == 6)
			ph[i].total_meals = arg_atoi(argv[5]);
		i++;
	}
	return (0);
}
