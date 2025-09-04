/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JuHyeon <juhyeonl@student.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:19:20 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/08/26 11:19:21 by JuHyeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_if_philo_died(t_philo *philo)
{
	long long	now;

	pthread_mutex_lock(&philo->info->meal_mutex);
	now = get_time_ms();
	if ((now - philo->last_meal) > philo->info->ttd)
	{
		pthread_mutex_unlock(&philo->info->meal_mutex);
		print_status(philo, "died");
		pthread_mutex_lock(&philo->info->meal_mutex);
		philo->info->someone_died = 1;
		pthread_mutex_unlock(&philo->info->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->meal_mutex);
	return (0);
}

static int	check_if_all_ate(t_info *info)
{
	int	all_ate;

	all_ate = 0;
	if (info->must_eat_cnt == -1)
		return (0);
	pthread_mutex_lock(&info->meal_mutex);
	if (info->finished_philos >= info->num_philo)
		all_ate = 1;
	pthread_mutex_unlock(&info->meal_mutex);
	return (all_ate);
}

void	*monitor_routine(void *arg)
{
	t_info		*info;
	int			i;

	info = (t_info *)arg;
	while (1)
	{
		i = 0;
		while (i < info->num_philo)
		{
			if (check_if_philo_died(&info->philos[i]))
				return (NULL);
			i++;
		}
		if (check_if_all_ate(info))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
