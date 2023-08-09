/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 06:27:06 by loandrad          #+#    #+#             */
/*   Updated: 2023/08/04 15:31:36 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	valid_arg(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (-1);
	while (*str != '\0')
	{
		if (is_digit(*str) != 1 && *str != ' ' && *str != '\t')
			return (-1);
		str++;
	}
	return (0);
}

int	arg_atoi(char *nb)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	if (valid_arg(nb) != 0)
		return (-1);
	while (nb[i] == ' ')
		i++;
	if (nb[i] == '+' || nb[i] == '-')
	{
		if (nb[i] == '-')
			return (-1);
		i++;
	}
	while (nb[i] && is_digit(nb[i]) == 1)
	{
		result = result * 10;
		result = result + (nb[i] - 48);
		i++;
	}
	if (result > INT_MAX)
		return (-1);
	return (result);
}

static int	valid_param(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (-1);
	if (arg_atoi(argv[1]) <= 0 || arg_atoi(argv[2]) < 0
		|| arg_atoi(argv[3]) < 0 || arg_atoi(argv[4]) < 0
		|| (argc == 6 && arg_atoi(argv[5]) <= 0))
		return (-1);
	return (0);
}

int	arg_check(int argc, char *argv[], t_philo **ph)
{
	if (valid_param(argc, argv) == -1)
		return (-1);
	*ph = malloc(sizeof(t_philo) * arg_atoi(argv[1]));
	if (!*ph)
		return (-1);
	if (init_philos(argc, argv, *ph) == -1)
	{
		free_exit(*ph, 1);
		return (-1);
	}
	if (init_mutexes(*ph) == -1)
	{
		free_exit(*ph, 2);
		return (-1);
	}
	return (0);
}
