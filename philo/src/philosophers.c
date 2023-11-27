/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:47:14 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/27 16:40:22 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philosophers(t_philosopher *philosophers)
{
	int	i;

	i = 1;
	pthread_mutex_destroy(philosophers[0].global_mutex);
	free(philosophers[0].global_mutex);
	while (i < philosophers->args->philo_count)
	{
		pthread_mutex_destroy(philosophers[i].philo_mutex);
		free(philosophers[i].philo_mutex);
		i++;
	}
	pthread_mutex_destroy(philosophers->philo_mutex);
	free(philosophers->philo_mutex);
	free(philosophers->death_flag);
	free(philosophers);
}

static void	*loop_philosophers(
	t_philosopher *philosophers,
	t_args *args,
	pthread_mutex_t *forks,
	int *death_flag)
{
	int				id;
	pthread_mutex_t	*global_mutex;
	pthread_mutex_t	*philo_mutex;

	id = 0;
	global_mutex = malloc(sizeof(pthread_mutex_t));
	if (!global_mutex || pthread_mutex_init(global_mutex, NULL) != 0)
		return (NULL);
	while (id < args->philo_count)
	{
		philo_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo_mutex, NULL);
		philosophers[id].id = id;
		philosophers[id].args = args;
		philosophers[id].global_mutex = global_mutex;
		philosophers[id].death_flag = death_flag;
		philosophers[id].philo_mutex = philo_mutex;
		philosophers[id].left_fork = &forks[args->philo_count - 1];
		if (id > 0)
			philosophers[id].left_fork = &forks[id - 1];
		philosophers[id].right_fork = &forks[id];
		id++;
	}
	return (philosophers);
}

t_philosopher	*init_philosophers(t_args *args, pthread_mutex_t *forks)
{
	t_philosopher	*philosophers;
	int				philo_arr_size;
	int				*death_flag;

	philo_arr_size = args->philo_count * sizeof(t_philosopher) + 1;
	philosophers = malloc(philo_arr_size);
	if (!philosophers)
		return (NULL);
	memset(philosophers, 0, philo_arr_size);
	death_flag = malloc(sizeof(int));
	if (!death_flag)
		return (NULL);
	*death_flag = 0;
	loop_philosophers(philosophers, args, forks, death_flag);
	return (philosophers);
}

int	start_the_feast(t_philosopher *philosophers)
{
	pthread_t	*threads;
	pthread_t	*monitoring;
	int			i;

	threads = malloc(sizeof(pthread_t) * philosophers[0].args->philo_count);
	if (!threads)
		return (-1);
	memset(threads, 0, sizeof(pthread_t) * philosophers[0].args->philo_count);
	i = 0;
	monitoring = malloc(sizeof(pthread_t));
	pthread_create(monitoring, NULL, (void *) monitoring_thread, philosophers);
	ft_wait(1000);
	while (i < philosophers->args->philo_count)
	{
		if (pthread_create(&threads[i], NULL, (void *) philosopher,
				&philosophers[i]))
			return (-1);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
	pthread_join(*monitoring, NULL);
	free(monitoring);
	free(threads);
	return (1);
}
