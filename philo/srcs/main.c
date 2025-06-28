/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 16:31:52 by juhyeonl          #+#    #+#             */
/*   Updated: 2025-06-19 16:31:52 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void destroy(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_cnt)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(&data->philos[i]->mt_meal);
        free(data->philos[i]);
        i++;
    }
    free(data->philos);
    free(data->forks);
    pthread_mutex_destroy(&data->mt_print);
    pthread_mutex_destroy(&data->mt_terminate);
}

int main(int argc, char **argv)
{
    t_data data;
    int    i;

    if (init_data(&data, argc, argv))
        return (1);
    // printf("DEBUG: philo_cnt=%d\n", data.philo_cnt);
    // printf("DEBUG: argv[1]=%s, parsed=%d\n", argv[1], ft_atoi(argv[1]));
    // printf("DEBUG init complete: philo_cnt=%d, time_to_die=%zu, ...\n", data.philo_cnt, data.time_to_die);
    data.start_ms = get_time();
    i = -1;
    while (++i < data.philo_cnt)
        data.philos[i]->last_meal_ms = data.start_ms;
    i = -1;
    while (++i < data.philo_cnt)
        pthread_create(&data.philos[i]->thread, NULL, philo_routine, data.philos[i]);
    pthread_create(&data.monitor_thread, NULL, monitor_fn, &data);
    i = -1;
    while (++i < data.philo_cnt)
        pthread_join(data.philos[i]->thread, NULL);
    pthread_join(data.monitor_thread, NULL);
    destroy(&data);
    return (0);
}
