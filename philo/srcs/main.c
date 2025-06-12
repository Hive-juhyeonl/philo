/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:49:10 by ljh3900           #+#    #+#             */
/*   Updated: 2025/06/12 03:42:38 by ljh3900          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	valid_check(int ac, char **av)
{
	int	i;
	int	j;
	int	val;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		val = ft_atoi(av[i]);
		if (val <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	start_simul(t_info *info)
{
	int			i;
	pthread_t	monitor;

	info->start_time = get_time_ms();
	i = 0;
	while (i < info->num_philo)
	{
		info->philo_arr[i].last_meal = info->start_time;
		i++;
	}
	i = 0;
	while (i < info->num_philo)
	{
		if (pthread_create(&info->philo_arr[i].thread, NULL,
				philo_routine, &info->philo_arr[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, (void *)monitor_routine, info) != 0)
		return (1);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < info->num_philo)
	{
		pthread_join(info->philo_arr[i].thread, NULL);
		i++;
	}
	return (0);
}

static void	clean_up(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->print_mutex);
	pthread_mutex_destroy(&info->meal_mutex);
	free(info->forks);
	free(info->philo_arr);
}

int main(int ac, char **av)
{
	t_info	info;

	if (valid_check(ac, av))
		return (ft_putstr_fd("Invalid arguments\n", 2));
	if (info_init(&info, ac, av))
		return (ft_putstr_fd("Info initialization failed\n", 2));
	if (philo_init(&info))
		return (ft_putstr_fd("Philo initialization failed\n", 2));
	if (start_simul(&info))
		return (ft_putstr_fd("Simulation failed\n", 2));
	clean_up(&info);
	return (0);
}
