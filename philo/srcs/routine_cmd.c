/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:14:50 by ljh3900           #+#    #+#             */
/*   Updated: 2025/06/12 04:49:33 by ljh3900          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_up_fork(t_philo *philo)
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

void	ft_down_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->meal_mutex);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->info->meal_mutex);
	print_status(philo, "is eating");
	philo->eat_cnt++;
	if (philo->info->m_eat_cnt > 0 && philo->eat_cnt == philo->info->m_eat_cnt)
	{
		pthread_mutex_lock(&philo->info->meal_mutex);
		philo->info->finished_cnt++;
		pthread_mutex_unlock(&philo->info->meal_mutex);
	}

	msleep(philo->info->tt_eat);
}

void	ft_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	msleep(philo->info->tt_sleep);
}

void	ft_think(t_philo *philo)
{
	print_status(philo, "is thinking");
	if (philo->info->num_philo % 2)
		msleep(philo->info->tt_eat);
	// else
	// 	msleep(philo->info->tt_eat * 2);
}
