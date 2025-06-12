/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:42:38 by JuHyeon           #+#    #+#             */
/*   Updated: 2025/06/12 02:55:50 by ljh3900          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

struct s_philo
{
	int				id;
	int				eat_cnt;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
};

struct s_info
{
	long long		start_time;
	long long		tt_die;
	long long		tt_eat;
	long long		tt_sleep;
	int				num_philo;
	int				m_eat_cnt;
	int				finished_cnt;
	bool			someone_died;
	t_philo			*philo_arr;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
};

/* init.c */
int			info_init(t_info *info, int ac, char **av);
int			philo_init(t_info *info);
int			ft_atoi(char *str);

/* monitor.c */
void		monitor_routine(void *arg);

/* routine.c */
void		*philo_routine(void *arg);
void		ft_died(t_philo *philo);

/* routine_cmd.c */
void		ft_up_fork(t_philo *philo);
void		ft_down_fork(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);

/* utils.c */
void		msleep(long long ms);
long long	get_time_ms(void);
void		ft_putnbr(int n);
void		print_status(t_philo *philo, char *msg);
int			ft_putstr_fd(char *msg, int fd);

#endif
