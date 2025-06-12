/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:36:06 by ljh3900           #+#    #+#             */
/*   Updated: 2025/06/12 02:59:12 by ljh3900          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	msleep(long long ms)
{
	long long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
		usleep(100);
}

void	print_status(t_philo *philo, char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->info->print_mutex);
	if (!philo->info->someone_died)
	{
		timestamp = get_time_ms() - philo->info->start_time;
		ft_putnbr(timestamp);
		write(1, " ", 1);
		ft_putnbr(philo->id);
		write(1, " ", 1);
		ft_putstr_fd(msg, 1);
		write(1, "\n", 1);
	}
	pthread_mutex_unlock(&philo->info->print_mutex);
}

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_putnbr(int n)
{
	char	c;

	if (n >= 10)
		ft_putnbr(n / 10);
	c = '0' + (n % 10);
	write(1, &c , 1);
}

int	ft_putstr_fd(char *msg, int fd)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(fd, &msg[i], 1);
		i++;
	}
	return (1);
}
