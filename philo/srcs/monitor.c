/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JuHyeon <juhyeonl@student.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:42:38 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/02/28 15:06:01 by JuHyeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitor_routine(void *arg)
{
	t_info		*info;
	int			i;
	long long	now;

	info = (t_info *)arg;
	while (!info->someone_died && info->finished_philos < info->num_philo)
	{
		i = 0;
		while (i < info->num_philo)
		{
			pthread_mutex_lock(&info->meal_mutex);
			now = get_time_ms();
			if ((now - info->philos[i].last_meal) > info->ttd)
			{
				info->someone_died = 1;
				pthread_mutex_lock(&info->print_mutex);
				printf("%lld %d died\n",
					now - info->start_time, info->philos[i].id);
				pthread_mutex_unlock(&info->print_mutex);
				pthread_mutex_unlock(&info->meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&info->meal_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
