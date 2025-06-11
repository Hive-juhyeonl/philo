/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JuHyeon <juhyeonl@student.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:42:38 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/02/28 15:06:01 by JuHyeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy_mutex(t_info *info)
{
	int	i;

	pthread_mutex_destroy(&info->print_mutex);
	pthread_mutex_destroy(&info->meal_mutex);
	i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
}

void	free_all(t_info *info)
{
	if (info->forks)
		free(info->forks);
	if (info->philos)
		free(info->philos);
}
