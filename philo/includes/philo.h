/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JuHyeon <JuHyeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:18:37 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/09/08 03:30:48 by JuHyeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;
typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	int				id;
	int				eat_cnt;
	long long		last_meal;
	pthread_t		thread;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
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
	t_mutex			print_mutex;
	t_mutex			meal_mutex;
	t_mutex			*forks;
	t_philo			*philos;
}	t_info;

// utils.c
long long	get_time_ms(void);
// void		my_usleep(long long ms);
void		my_usleep(long long ms, t_info *info);
void		print_status(t_philo *philo, const char *msg);
int			ft_atoi(const char *str);
int			simulation_finished(t_info *info);

// init.c
int			init_info(t_info *info, int argc, char **argv);
int			init_mutex(t_info *info);
int			init_philos(t_info *info);

// philo_routine.c
void		*philo_routine(void *arg);
void		*philo_routine_single(void *arg);

// monitor.c
void		*monitor_routine(void *arg);

// clean.c
void		destroy_mutex(t_info *info);
void		free_all(t_info *info);
int			cleanup_on_error(t_info *info, int created_count);

// life.c
// void		take_forks(t_philo *philo);
void		take_forks_even(t_philo *philo);
void		take_forks_odd(t_philo *philo);
void		eat(t_philo *philo);
void		put_forks(t_philo *philo);

#endif
