/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:04:05 by ljh3900           #+#    #+#             */
/*   Updated: 2025/06/12 03:49:36 by ljh3900          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	monitor_routine(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	while (1)
	{
		i = 0;
		while (i < info->num_philo)
		{
			pthread_mutex_lock(&info->meal_mutex);
			if (get_time_ms() - info->philo_arr[i].last_meal >= info->tt_die)
			{
				ft_died(&info->philo_arr[i]);
				pthread_mutex_unlock(&info->meal_mutex);
				return ;
			}
			pthread_mutex_unlock(&info->meal_mutex);
			i++;
		}
		usleep(500);
	}
}
