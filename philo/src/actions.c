/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:12:25 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/09 09:02:00 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_for_eat(t_philosopher *philo)
{
	if ((philo->id + 1) % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	if ((philo->id + 1) % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
}

void	*die(t_philosopher *philo, size_t start_time, int id)
{
	printf("%zu %d died\n",
		get_time() - start_time, id + 1);
	pthread_mutex_lock(philo->global_mutex);
	*philo->death_flag = 1;
	pthread_mutex_unlock(philo->global_mutex);
	return (NULL);
}

void	eat(t_philosopher *philo)
{
	printf("%zu %d is eating\n", get_time() - philo->start_time, philo->id + 1);
	ft_wait(philo->args->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philosopher *philo)
{
	printf("%zu %d is sleeping\n",
		get_time() - philo->start_time, philo->id + 1);
	ft_wait(philo->args->time_to_sleep);
}

void	think(t_philosopher *philo)
{
	printf("%zu %d is thinking\n",
		get_time() - philo->start_time, philo->id + 1);
}
