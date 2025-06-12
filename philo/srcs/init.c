/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:00:46 by ljh3900           #+#    #+#             */
/*   Updated: 2025/06/12 04:16:56 by ljh3900          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			sign = -1;
	}
	while ('0' <= *str && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}

int	info_init(t_info *info, int ac, char **av)
{
	int	i;

	memset(info, 0, sizeof(t_info));
	info->num_philo = ft_atoi(av[1]);
	info->tt_die = ft_atoi(av[2]);
	info->tt_eat = ft_atoi(av[3]);
	info->tt_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->m_eat_cnt = ft_atoi(av[5]);
	else
		info->m_eat_cnt = -1;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (!info->forks)
	{
		write(2, "[DEBUG] : forks fail\n", 21);
		return (1);
	}
	i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
	info->philo_arr = malloc(sizeof(t_philo) * info->num_philo);
	if (!info->philo_arr)
	{
		write(2, "[DEBUG] : philo_arr fail\n", 25);
		return (1);
	}
	pthread_mutex_init(&info->print_mutex, NULL);
	pthread_mutex_init(&info->meal_mutex, NULL);
	return (0);
}

int	philo_init(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		info->philo_arr[i].id = i + 1;
		info->philo_arr[i].eat_cnt = 0;
		info->philo_arr[i].last_meal = 0;
		info->philo_arr[i].left_fork = &info->forks[i];
		info->philo_arr[i].right_fork = &info->forks[(i + 1) % info->num_philo];
		info->philo_arr[i].info = info;
		i++;
	}
	return (0);
}
