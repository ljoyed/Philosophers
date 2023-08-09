/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 06:27:28 by loandrad          #+#    #+#             */
/*   Updated: 2023/08/03 16:01:11 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->ph_num)
	{
		pthread_join(ph[i].philo, NULL);
		i++;
	}
}

static void	destroy_mutexes(t_philo *ph)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(ph->lock);
	while (i < ph->ph_num)
	{
		pthread_mutex_destroy(&ph->forks[i]);
		i++;
	}
}

void	free_exit(t_philo *ph, int code)
{
	if (code == 1)
		free(ph);
	else
	{
		destroy_mutexes(ph);
		if (ph->lock)
			free(ph->lock);
		if (ph->forks)
			free(ph->forks);
		if (ph->dead)
			free(ph->dead);
		if (ph->ate)
			free(ph->ate);
		if (ph)
			free(ph);
	}
}
