/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 16:31:01 by juhyeonl          #+#    #+#             */
/*   Updated: 2025-06-19 16:31:01 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void take_forks(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	print_state(p, "has taken a fork");
	pthread_mutex_lock(p->right_fork);
	print_state(p, "has taken a fork");
}

static void put_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

static void solo_routine(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	print_state(p, "has taken a fork");
	precise_usleep(p->data->time_to_die);
	print_state(p, "died");
	pthread_mutex_unlock(p->left_fork);
}

static void	group_routine(t_philo *p)
{
	if (p->id % 2 == 0)
		precise_usleep(p->data->time_to_eat);
	while (!check_terminate(p->data))
	{
		take_forks(p);
		p->meal_eaten++;
		pthread_mutex_lock(&p->mt_meal);
		p->last_meal_ms = get_time();
		pthread_mutex_unlock(&p->mt_meal);
		print_state(p, "is eating");
		precise_usleep(p->data->time_to_eat);
		put_forks(p);
		if (p->data->must_eat > 0 && p->meal_eaten >= p->data->must_eat && !p->is_full)
		{
			p->is_full = true;
			p->data->full_count++;
		}
		print_state(p, "is sleeping");
		precise_usleep(p->data->time_to_sleep);
		print_state(p, "is thinking");
		usleep(1);
	}
}

void *philo_routine(void *arg)
{
	t_philo	*p;

	p = arg;
	// printf("DEBUG philo %d started, last_meal_ms=%zu\n", p->id, p->last_meal_ms);
	if (p->data->philo_cnt == 1)
		solo_routine(p);
	else
		group_routine(p);
	return (NULL);
}
