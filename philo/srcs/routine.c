/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:12:35 by ljh3900           #+#    #+#             */
/*   Updated: 2025/06/12 04:45:46 by ljh3900          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	philo->info->someone_died = true;
	ft_putnbr(get_time_ms() - philo->info->start_time);
	write(1, " ", 1);
	ft_putnbr(philo->id);
	write(1, " died\n", 6);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->info->num_philo == 1)
	{
		ft_up_fork(philo);
		msleep(philo->info->tt_die);
		ft_died(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		msleep(philo->info->tt_eat);
	while (!philo->info->someone_died)
	{
		ft_up_fork(philo);
		ft_eat(philo);
		ft_down_fork(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
