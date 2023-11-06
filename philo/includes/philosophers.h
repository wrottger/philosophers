/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:13:15 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/06 19:40:36 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
};

typedef struct s_args
{
	int		philo_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat_count;
}t_args;


typedef struct s_philosopher
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*print;
	t_args				*args;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}t_philosopher;


// cleanup.c
void			cleanup(
					t_philosopher *philosophers,
					pthread_mutex_t *forks,
					t_args *args);

// ft_atoi.c
int				ft_atoi(const char *str);

// initialization.c
int				initialization(
					char**argv,
					t_args *args,
					pthread_mutex_t *forks,
					t_philosopher *philosophers);

// arguments.c
t_args			*init_args(char **argv);

// philosophers.c
t_philosopher	*init_philosophers(t_args *args, pthread_mutex_t *forks);
int				start_the_feast(t_philosopher *philosophers);
void			cleanup_philosophers(t_philosopher *philosophers);

// mutexes.c
pthread_mutex_t	*init_forks(int philo_count);

#endif
