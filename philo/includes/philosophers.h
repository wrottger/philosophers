/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:13:15 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/09 09:02:00 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	int				philo_count;
	unsigned int	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
}t_args;

typedef struct s_philosopher
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*philo_mutex;
	size_t				last_eat;
	pthread_mutex_t		*global_mutex;
	int					*death_flag;
	t_args				*args;
	size_t				start_time;
	int					eat_count;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}t_philosopher;

// actions.c
void			wait_for_eat(t_philosopher *philo);
void			*die(t_philosopher *philo, size_t start_time, int id);
void			eat(t_philosopher *philo);
void			philo_sleep(t_philosopher *philo);
void			think(t_philosopher *philo);

// cleanup.c
void			cleanup(
					t_philosopher *philosophers,
					pthread_mutex_t *forks,
					t_args *args);

// ft_atoi.c
int				ft_atoi(const char *str);

// initialization.c
int				initialization(
					char **argv,
					t_args **args,
					pthread_mutex_t **forks,
					t_philosopher **philosophers);

// monitoring.c
void			*monitoring_thread(t_philosopher *philo);

// arguments.c
t_args			*init_args(char **argv);

// mutexes.c
pthread_mutex_t	*init_forks(int philo_count);
void			free_forks(pthread_mutex_t *forks, int philo_count);

// philosopher.c
void			*philosopher(t_philosopher *philo);

// philosophers.c
t_philosopher	*init_philosophers(t_args *args, pthread_mutex_t *forks);
int				start_the_feast(t_philosopher *philosophers);
void			cleanup_philosophers(t_philosopher *philosophers);
void			free_philosophers(t_philosopher *philosophers);

// time.c
size_t			get_time(void);
void			ft_wait(size_t time);

#endif
