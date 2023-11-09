/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:44:08 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/09 09:02:00 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	sync_start_time(t_philosopher *philo, size_t *start_time)
{
	int		id;

	id = 0;
	pthread_mutex_lock(philo->global_mutex);
	ft_wait(1000);
	philo->start_time = get_time();
	*start_time = philo->start_time;
	while (id < philo->args->philo_count)
	{
		philo[id].last_eat = *start_time;
		philo[id].start_time = *start_time;
		id++;
	}
	pthread_mutex_unlock(philo->global_mutex);
}

static void	*finish_dinner(t_philosopher *philo)
{
	pthread_mutex_lock(philo->global_mutex);
	*philo->death_flag = 1;
	pthread_mutex_unlock(philo->global_mutex);
	return (NULL);
}

void	*monitoring_thread(t_philosopher *philo)
{
	int		id;
	size_t	last_eat_time;
	size_t	start_time;
	int		dinner_finished;

	sync_start_time(philo, &start_time);
	id = 0;
	while (1)
	{
		dinner_finished = 1;
		while (id <= philo->args->philo_count - 1)
		{
			pthread_mutex_lock(philo[id].philo_mutex);
			last_eat_time = philo[id].last_eat;
			dinner_finished
				&= (philo[id].eat_count >= philo->args->must_eat_count);
			pthread_mutex_unlock(philo[id].philo_mutex);
			if (get_time() - last_eat_time >= philo->args->time_to_die)
				return (die(&philo[id], start_time, id));
			id++;
		}
		if (philo->args->must_eat_count != -1 && dinner_finished)
			return (finish_dinner(philo));
		id = 0;
	}
}
