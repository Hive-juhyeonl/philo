/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JuHyeon <juhyeonl@student.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:42:38 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/02/28 15:06:01 by JuHyeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	start_philo_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		if (pthread_create(&info->philos[i].thread, NULL,
				philo_routine, &info->philos[i]) != 0)
			return (1);
		usleep(100);
		i++;
	}
	return (0);
}

static int	start_monitor_thread(t_info *info, pthread_t *monitor)
{
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

int	main(int argc, char **argv)
{
	t_info		info;
	pthread_t	monitor;

	if (init_info(&info, argc, argv)
		|| init_mutex(&info)
		|| init_philos(&info)
		|| start_philo_threads(&info)
		|| start_monitor_thread(&info, &monitor))
	{
		printf("Error: initialization or thread creation failed\n");
		return (1);
	}
	wait_for_threads(&info, monitor);
	destroy_mutex(&info);
	free_all(&info);
	return (0);
}
