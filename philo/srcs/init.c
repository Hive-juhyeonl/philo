/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 16:30:21 by juhyeonl          #+#    #+#             */
/*   Updated: 2025-06-19 16:30:21 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	parse_args(t_data *d, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (1);
	d->philo_cnt     = ft_atoi(av[1]);
	d->time_to_die   = (size_t)ft_atoi(av[2]);
	d->time_to_eat   = (size_t)ft_atoi(av[3]);
	d->time_to_sleep = (size_t)ft_atoi(av[4]);
	if (ac == 6)
		d->must_eat = (int)ft_atoi(av[5]);
	else
		d->must_eat = -1;
	if (d->philo_cnt < 1
	 || d->time_to_die == 0
	 || d->time_to_eat == 0
	 || d->time_to_sleep == 0
	 || (ac == 6 && d->must_eat < 1))
		return (1);
	return (0);
}

static int init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_mutex) * data->philo_cnt);
	if (!data->forks)
		return (write(2, "malloc Error\n", 13), 1);
	i = 0;
	while (i < data->philo_cnt)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (write(2, "mutex_init Error\n", 18), 1);
		i++;
	}
	if (pthread_mutex_init(&data->mt_print, NULL)
	 || pthread_mutex_init(&data->mt_terminate, NULL))
		return (write(2, "mutex_init Error\n", 18), 1);
	data->someone_died = false;
	data->full_count   = 0;
	return (0);
}

static int init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo *) * data->philo_cnt);
	if (!data->philos)
		return (write(2, "malloc Error\n", 13), 1);
	i = 0;
	while (i < data->philo_cnt)
	{
		data->philos[i] = malloc(sizeof(t_philo));
		if (!data->philos[i])
			return (write(2, "malloc Error\n", 13), 1);
		data->philos[i]->id           = i + 1;
		data->philos[i]->data         = data;
		data->philos[i]->meal_eaten   = 0;
		data->philos[i]->is_full      = false;
		data->philos[i]->last_meal_ms = data->start_ms;
		if (pthread_mutex_init(&data->philos[i]->mt_meal, NULL))
			return (write(2, "mutex_init Error\n", 18), 1);
		data->philos[i]->left_fork   = &data->forks[i];
		data->philos[i]->right_fork  = &data->forks[(i + 1) % data->philo_cnt];
		i++;
	}
	return (0);
}

int init_data(t_data *data, int argc, char **argv)
{
	if (parse_args(data, argc, argv))
		return (printf("Usage: %s number_of_philos \
			time_to_die time_to_eat time_to_sleep [must_eat]\n", argv[0]), 1);
	if (init_mutexes(data))
		return (1);
	if (init_philos(data))
		return (1);
	return (0);
}
