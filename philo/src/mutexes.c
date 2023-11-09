/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:00:28 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/08 20:47:44 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*init_forks(int philo_count)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(
			philo_count * sizeof(pthread_mutex_t) + 1
			);
	if (!forks)
		return (NULL);
	while (i < philo_count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

void	free_forks(pthread_mutex_t *forks, int philo_cout)
{
	int	i;

	i = 0;
	while (i < philo_cout)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}
