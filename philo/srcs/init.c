/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JuHyeon <juhyeonl@student.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:42:38 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/02/28 15:06:01 by JuHyeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_info(t_info *info, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (1);
	info->num_philo = ft_atoi(av[1]);
	info->ttd = ft_atoi(av[2]);
	info->tte = ft_atoi(av[3]);
	info->tts = ft_atoi(av[4]);
	if (ac == 6)
		info->must_eat_cnt = ft_atoi(av[5]);
	else
		info->must_eat_cnt = -1;
	if (info->num_philo < 1 || info->ttd < 0 || info->tte < 0 || info->tts < 0)
		return (1);
	info->finished_philos = 0;
	info->someone_died = 0;
	info->start_time = get_time_ms();
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	info->philos = malloc(sizeof(t_philo) * info->num_philo);
	if (!info->forks || !info->philos)
		return (1);
	return (0);
}

int	init_mutex(t_info *info)
{
	int	i;

	if (pthread_mutex_init(&info->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&info->meal_mutex, NULL) != 0)
		return (1);
	i = 0;
	while (i < info->num_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		info->philos[i].id = i + 1;
		info->philos[i].eat_cnt = 0;
		info->philos[i].last_meal = get_time_ms();
		info->philos[i].left_fork = &info->forks[i];
		info->philos[i].right_fork = &info->forks[(i + 1) % info->num_philo];
		info->philos[i].info = info;
		i++;
	}
	return (0);
}
