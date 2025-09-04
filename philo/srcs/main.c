/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:19:50 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/08/26 13:37:16 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	start_threads(t_info *info, pthread_t *monitor)
{
	int	i;

	i = 0;
	info->start_time = get_time_ms();
	while (i < info->num_philo)
	{
		pthread_mutex_lock(&info->meal_mutex);
		info->philos[i].last_meal = info->start_time;
		pthread_mutex_unlock(&info->meal_mutex);
		if (pthread_create(&info->philos[i].thread, NULL,
				philo_routine, &info->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_routine, info) != 0)
		return (1);
	return (0);
}

static void	wait_for_threads(t_info *info, pthread_t monitor)
{
	int	i;

	pthread_join(monitor, NULL);
	i = 0;
	while (i < info->num_philo)
	{
		pthread_join(info->philos[i].thread, NULL);
		i++;
	}
}

static int	run_simulation(t_info *info)
{
	pthread_t	monitor;

	if (info->num_philo == 1)
	{
		info->start_time = get_time_ms();
		printf("%lld %d %s\n", 0LL, 1, "has taken a fork");
		my_usleep(info->ttd);
		printf("%lld %d %s\n", (long long)info->ttd, 1, "died");
		return (0);
	}
	if (start_threads(info, &monitor) != 0)
	{
		printf("Error: Thread creation failed\n");
		return (1);
	}
	wait_for_threads(info, monitor);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (init_info(&info, argc, argv) != 0)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (init_mutex(&info) != 0 || init_philos(&info) != 0)
	{
		printf("Error: Initialization failed\n");
		destroy_mutex(&info);
		free_all(&info);
		return (1);
	}
	if (run_simulation(&info) != 0)
	{
		destroy_mutex(&info);
		free_all(&info);
		return (1);
	}
	destroy_mutex(&info);
	free_all(&info);
	return (0);
}
