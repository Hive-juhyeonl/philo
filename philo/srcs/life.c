/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JuHyeon <JuHyeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 23:15:48 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/09/07 23:16:10 by JuHyeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&info->meal_mutex);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&info->meal_mutex);
	print_status(philo, "is eating");
	my_usleep(info->tte);
	philo->eat_cnt++;
	if (info->must_eat_cnt != -1 && philo->eat_cnt >= info->must_eat_cnt)
	{
		pthread_mutex_lock(&info->meal_mutex);
		info->finished_philos++;
		pthread_mutex_unlock(&info->meal_mutex);
	}
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
