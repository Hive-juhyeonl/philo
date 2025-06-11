/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JuHyeon <juhyeonl@student.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:42:38 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/02/28 15:06:01 by JuHyeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	take_forks(t_philo *philo)
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

static void	eat(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	// pthread_mutex_lock(&info->meal_mutex);
	// philo->last_meal = get_time_ms();
	// pthread_mutex_unlock(&info->meal_mutex);
	pthread_mutex_lock(&info->meal_mutex);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&info->meal_mutex);
	print_status(philo, "is eating");
	my_usleep(info->tte);
	philo->eat_cnt++;
	if (info->must_eat_cnt != -1 && philo->eat_cnt >= info->must_eat_cnt)
	{
		pthread_mutex_lock(&info->print_mutex);
		info->finished_philos++;
		pthread_mutex_unlock(&info->print_mutex);
	}
}

static void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	// if (philo->id % 2 == 0)
	// 	my_usleep(1000);
	if (philo->id % 2 == 0)
		my_usleep(info->tte);
	while (!info->someone_died && info->finished_philos < info->num_philo)
	{
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		print_status(philo, "is sleeping");
		my_usleep(info->tts);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
