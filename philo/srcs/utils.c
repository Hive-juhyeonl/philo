/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 16:24:20 by juhyeonl          #+#    #+#             */
/*   Updated: 2025-06-19 16:24:20 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t get_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000UL + tv.tv_usec / 1000UL);
}

void precise_usleep(size_t ms)
{
	size_t start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(100);
}

static int ft_strcmp(const char *s1, const char *s2)
{
    size_t i;
	
	i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void print_state(t_philo *p, const char *msg)
{
	if (p->data->someone_died && ft_strcmp(msg, "died"))
		return ;
	pthread_mutex_lock(&p->data->mt_print);
	printf("%zu %d %s\n", get_time() - p->data->start_ms, p->id, msg);
	pthread_mutex_unlock(&p->data->mt_print);
}

bool check_terminate(t_data *data)
{
	if (data->someone_died)
		return (true);
	if (data->must_eat > 0 && data->full_count >= data->philo_cnt)
		return (true);
	return (false);
}
