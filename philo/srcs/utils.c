/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JuHyeon <JuHyeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:19:36 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/08/26 11:30:50 by JuHyeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	my_usleep(long long ms)
{
	long long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < ms)
	{
		if (simulation_finished(NULL))
			break ;
		usleep(500);
	}
}

int	simulation_finished(t_info *info)
{
	int	died;
	int	finished;

	if (!info)
		return (0);
	pthread_mutex_lock(&info->meal_mutex);
	died = info->someone_died;
	finished = (info->must_eat_cnt != -1
			&& info->finished_philos >= info->num_philo);
	pthread_mutex_unlock(&info->meal_mutex);
	return (died || finished);
}

void	print_status(t_philo *philo, const char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->info->print_mutex);
	if (!simulation_finished(philo->info))
	{
		timestamp = get_time_ms() - philo->info->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->info->print_mutex);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			sign = -1;
	}
	while ('0' <= *str && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}
