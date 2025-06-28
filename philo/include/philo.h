/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 16:19:54 by juhyeonl          #+#    #+#             */
/*   Updated: 2025-06-19 16:19:54 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

typedef pthread_mutex_t   t_mutex;
typedef pthread_t         t_thread;

typedef struct s_philo  t_philo;
typedef struct s_data   t_data;

struct s_philo
{
	int			id;
	t_data		*data;
	int			meal_eaten;
	bool		is_full;
	size_t		last_meal_ms;
	t_mutex		mt_meal;
	t_thread	thread;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
};

struct s_data
{
	int			philo_cnt;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			must_eat;
	t_mutex		*forks;
	t_mutex		mt_print;
	t_mutex		mt_terminate;
	bool		someone_died;
	int			full_count;
	size_t		start_ms;
	t_philo		**philos;
	t_thread	monitor_thread;
};

size_t  get_time(void);
void    precise_usleep(size_t ms);
void    print_state(t_philo *p, const char *msg);
bool    check_terminate(t_data *data);
int     init_data(t_data *data, int argc, char **argv);
void    *philo_routine(void *arg);
void    *monitor_fn(void *arg);
int		ft_atoi(const char *nptr);

#endif
