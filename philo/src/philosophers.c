/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:47:14 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/08 19:52:28 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*loop_philosophers(
	t_philosopher *philosophers,
	t_args *args,
	pthread_mutex_t *forks,
	int *death_flag)
{
	int				id;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*time_mutex;

	id = 0;
	death_mutex = malloc(sizeof(pthread_mutex_t));
	if (!death_mutex || pthread_mutex_init(death_mutex, NULL) != 0)
		return (NULL);
	while (id < args->philo_count)
	{
		time_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(time_mutex, NULL);
		philosophers[id].id = id;
		philosophers[id].args = args;
		philosophers[id].death_mutex = death_mutex;
		philosophers[id].death_flag = death_flag;
		philosophers[id].time_mutex = time_mutex;
		if (id > 0)
			philosophers[id].left_fork = &forks[id - 1];
		else
			philosophers[id].left_fork = &forks[args->philo_count - 1];
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
	return (1);
}
