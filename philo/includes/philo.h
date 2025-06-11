/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JuHyeon <juhyeonl@student.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:42:38 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/02/28 15:06:01 by JuHyeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int				id;
	int				eat_cnt;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
}	t_philo;

typedef struct s_info
{
	int				num_philo;
	int				ttd;
	int				tte;
	int				tts;
	int				must_eat_cnt;
	int				finished_philos;
	int				someone_died;
	long long		start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_info;

// utils.c
long long	get_time_ms(void);
void		my_usleep(long long ms);
void		print_status(t_philo *philo, const char *msg);
int			ft_atoi(const char *str);

// init.c
int			init_info(t_info *info, int argc, char **argv);
int			init_mutex(t_info *info);
int			init_philos(t_info *info);

// philo_routine.c
void		*philo_routine(void *arg);

// monitor.c
void		*monitor_routine(void *arg);

// clean.c
void		destroy_mutex(t_info *info);
void		free_all(t_info *info);

#endif
