/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 06:28:19 by loandrad          #+#    #+#             */
/*   Updated: 2023/08/04 18:35:35 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	death(t_philo *ph)
{
	long long	elapsed;

	elapsed = get_time();
	if (elapsed - ph->last_meal > ph->die_timer)
	{
		printf("%llu %d died\n", get_time() - ph->start, ph->id);
		*(ph->dead) += 1;
		return (1);
	}
	return (0);
}

static int	finished_eating(t_philo *ph)
{
	if (ph->total_meals != 0 && *(ph->ate) == ph->ph_num)
		return (1);
	return (0);
}

static void	checker(t_philo *ph)
{
	int				i;
	int				dead;
	int				ate;

	dead = 0;
	ate = 0;
	while (1)
	{
		i = 0;
		while (i < ph->ph_num)
		{
			pthread_mutex_lock(ph[i].lock);
			dead = death(&ph[i]);
			ate = finished_eating(&ph[i]);
			pthread_mutex_unlock(ph[i].lock);
			if (ate != 0 || dead != 0)
				return ;
			i++;
		}
	}
}

int	init_prog(int argc, char *argv[], t_philo **ph)
{
	if (arg_check(argc, argv, ph) == -1)
	{
		printf("%s", HLP_MSG);
		return (1);
	}
	make_threads(*ph, (*ph)->ph_num);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo	*ph;

	if (init_prog(argc, argv, &ph) != 0)
		return (1);
	checker(ph);
	join_threads(ph);
	if (*(ph->ate) == ph->ph_num || *(ph->dead) == 0)
		printf("%d philosophers ate %d times each!\n",
			ph->ph_num, ph->total_meals);
	free_exit(ph, 3);
	return (0);
}
