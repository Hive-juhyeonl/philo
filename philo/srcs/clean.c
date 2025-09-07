/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JuHyeon <JuHyeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:42:38 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/09/07 22:51:14 by JuHyeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	cleanup_on_error(t_info *info, int created_count)
{
	int	i;

	i = 0;
	while (i < created_count)
	{
		pthread_join(info->philos[i].thread, NULL);
		i++;
	}
	destroy_mutex(info);
	free_all(info);
	return (1);
}

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
