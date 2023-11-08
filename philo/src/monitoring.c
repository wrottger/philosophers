/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:44:08 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/08 15:05:34 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	sync_start_time(t_philosopher *philo, size_t *start_time)
{
	int		id;

	id = 0;
	pthread_mutex_lock(philo->death_mutex);
	ft_wait(1000);
	philo->start_time = get_time();
	*start_time = philo->start_time;
	while (id < philo->args->philo_count)
	{
		philo[id].last_eat = *start_time;
		philo[id].start_time = *start_time;
		id++;
	}
	pthread_mutex_unlock(philo->death_mutex);
}

void	*monitoring_thread(t_philosopher *philo)
{
	int		id;
	size_t	last_eat_time;
	size_t	start_time;

	sync_start_time(philo, &start_time);
	id = 0;
	while (1)
	{
		while (philo[id].id < philo->args->philo_count - 1)
		{
			pthread_mutex_lock(philo[id].time_mutex);
			last_eat_time = philo[id].last_eat;
			pthread_mutex_unlock(philo[id].time_mutex);
			if (get_time() - last_eat_time >= philo->args->time_to_die)
			{
				printf("%zu %d died\n", get_time() - start_time, philo[id].id + 1);
				pthread_mutex_lock(philo->death_mutex);
				*philo->death_flag = 1;
				pthread_mutex_unlock(philo->death_mutex);
				die(&philo[id]);
				return (NULL);
			}
			usleep(100);
			id++;
		}
		id = 0;
	}
}
