/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 06:29:55 by loandrad          #+#    #+#             */
/*   Updated: 2023/08/04 18:29:05 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->lock);
	if (*(philo->dead) == 0)
	{
		printf("%llu %d %s", get_time() - philo->start, philo->id, message);
	}
	pthread_mutex_unlock(philo->lock);
}

static void	philo_ate(t_philo *philo)
{
	print_message(philo, "is eating\n");
	pthread_mutex_lock(philo->lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->lock);
	slp_pause(philo->eat_timer);
	pthread_mutex_lock(philo->lock);
	philo->meal_num += 1;
	if (philo->total_meals != 0 && philo->meal_num == philo->total_meals)
		*(philo->ate) += 1;
	pthread_mutex_unlock(philo->lock);
}

static void	table(t_philo *philo)
{
	print_message(philo, "is thinking\n");
	pthread_mutex_lock(&philo->forks[philo->l_fork]);
	print_message(philo, "has taken a fork\n");
	if (philo->ph_num == 1)
	{
		pthread_mutex_unlock(&philo->forks[philo->l_fork]);
		slp_pause(philo->die_timer + 1);
		return ;
	}
	pthread_mutex_lock(&philo->forks[philo->r_fork]);
	print_message(philo, "has taken a fork\n");
	philo_ate(philo);
	pthread_mutex_unlock(&philo->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->forks[philo->r_fork]);
	print_message(philo, "is sleeping\n");
	slp_pause(philo->slp_timer);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		table(philo);
		pthread_mutex_lock(philo->lock);
		if (*(philo->ate) == philo->ph_num || *(philo->dead) > 0)
		{
			pthread_mutex_unlock(philo->lock);
			break ;
		}
		pthread_mutex_unlock(philo->lock);
	}
	return (NULL);
}

int	make_threads(t_philo *ph, int ph_num)
{
	int	i;

	i = 0;
	while (i < ph_num)
	{
		if (pthread_create(&ph[i].philo, NULL, routine, &ph[i]) != 0)
			return (-1);
		i++;
		usleep(40);
	}
	return (0);
}
