/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JuHyeon <JuHyeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:19:03 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/09/09 03:06:18 by JuHyeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine_single(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	my_usleep(philo->info->ttd, philo->info);
	print_status(philo, "died");
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

static void	philo_eat_sleep_think(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	usleep(500);
	if (philo->id % 2 == 0)
		take_forks_even(philo);
	else
		take_forks_odd(philo);
	if (simulation_finished(info))
	{
		put_forks(philo);
		return ;
	}
	eat(philo);
	put_forks(philo);
	if (simulation_finished(info))
		return ;
	print_status(philo, "is sleeping");
	my_usleep(info->tts, info);
	print_status(philo, "is thinking");
	if (info->num_philo % 2)
		usleep(500);
}

// static void	philo_eat_sleep_think(t_philo *philo)
// {
// 	t_info	*info;

// 	info = philo->info;
    
// 	// 생각하는 상태를 출력한 후, 잠시 대기하여 포크 경쟁을 완화합니다.
// 	print_status(philo, "is thinking");
// 	usleep(200); // 100ms 지연 추가
// 	if (philo->id % 2 == 0)
// 		take_forks_even(philo);
// 	else
// 		take_forks_odd(philo);
	
// 	if (simulation_finished(info))
// 	{
// 		put_forks(philo);
// 		return ;
// 	}
// 	eat(philo);
// 	put_forks(philo);
// 	if (simulation_finished(info))
// 		return ;
// 	print_status(philo, "is sleeping");
// 	my_usleep(info->tts, info);
// }

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	if (philo->id % 2 == 0)
		usleep(200);
	while (!simulation_finished(info))
		philo_eat_sleep_think(philo);
	return (NULL);
}
