/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 06:30:07 by loandrad          #+#    #+#             */
/*   Updated: 2023/08/03 16:04:21 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	slp_pause(long long msec)
{
	long long	now;
	long long	elapsed;

	now = get_time();
	elapsed = get_time();
	while (elapsed - now < msec)
	{
		usleep(100);
		elapsed = get_time();
	}
}
