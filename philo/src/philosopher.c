/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:12:18 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/09 09:02:00 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static	int	has_died(t_philosopher *philo)
{
	pthread_mutex_lock(philo->global_mutex);
	if (*(philo->death_flag))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->global_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->global_mutex);
	return (0);
}

static void	sync_start_time(t_philosopher *philo)
{
	pthread_mutex_lock(philo->global_mutex);
	pthread_mutex_unlock(philo->global_mutex);
	return ;
}

void	*philosopher(t_philosopher *philo)
{
	sync_start_time(philo);
	if ((philo->id + 1) % 2 == 0)
		usleep(2000);
	if (philo->left_fork == philo->right_fork)
		return (NULL);
	while (1)
	{
		usleep((philo->id) * (300 / philo->args->philo_count));
		wait_for_eat(philo);
		if (has_died(philo))
			return (NULL);
		pthread_mutex_lock(philo->philo_mutex);
		eat(philo);
		philo->last_eat = get_time();
		philo->eat_count++;
		pthread_mutex_unlock(philo->philo_mutex);
		if (has_died(philo))
			return (NULL);
		philo_sleep(philo);
		if (has_died(philo))
			return (NULL);
		think(philo);
	}
	return (NULL);
}
