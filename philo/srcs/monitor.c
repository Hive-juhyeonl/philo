/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 16:31:19 by juhyeonl          #+#    #+#             */
/*   Updated: 2025-06-19 16:31:19 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *monitor_fn(void *arg)
{
    t_data *d;
    int     i;

    d = arg;
    while (!check_terminate(d))
    {
        i = 0;
        while (i < d->philo_cnt && !(d->someone_died))
        {
            t_philo *p = d->philos[i];
            size_t   now = get_time();
            pthread_mutex_lock(&p->mt_meal);
            if (now - p->last_meal_ms > d->time_to_die)
            {
                d->someone_died = true;
                print_state(p, "died");
            }
            pthread_mutex_unlock(&p->mt_meal);
            i++;
        }
        if (d->must_eat > 0 && d->full_count >= d->philo_cnt)
            d->someone_died = true;
        usleep(1000);
    }
    return (NULL);
}
