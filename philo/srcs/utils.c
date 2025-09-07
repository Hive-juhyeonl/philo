/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JuHyeon <JuHyeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:19:36 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/09/08 02:08:33 by JuHyeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	my_usleep(long long ms, t_info *info)
{
	long long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < ms)
	{
		if (simulation_finished(info))
			break ;
		usleep(250);
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
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (sign == 1 && result > INT_MAX)
			return ((int)INT_MAX);
		if (sign == -1 && result > (long long)INT_MAX + 1)
			return ((int)INT_MIN);
		str++;
	}
	return ((int)(result * sign));
}
