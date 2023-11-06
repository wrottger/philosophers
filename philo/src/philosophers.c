/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:47:14 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/06 19:01:36 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	loop_philosophers(
	t_philosopher *philosophers,
	t_args *args,
	pthread_mutex_t *forks)
{
	int	id;

	id = 1;
	while (id < args->philo_count)
	{
		philosophers[id].id = id;
		philosophers[id].args = args;
		philosophers[id].forks = forks;
		if (id > 0)
			philosophers[id].left_fork = &forks[id - 1];
		else
			philosophers[id].left_fork = &forks[args->philo_count - 1];
		philosophers[id].right_fork = &forks[id];
		id++;
	}
}

t_philosopher	*init_philosophers(t_args *args, pthread_mutex_t *forks)
{
	t_philosopher	*philosophers;
	int				philo_arr_size;

	philo_arr_size = args->philo_count * sizeof(t_philosopher) + 1;
	philosophers = malloc(philo_arr_size);
	if (!philosophers)
		return (NULL);
	memset(philosophers, 0, philo_arr_size);
	loop_philosophers(philosophers, args, forks);
	return (philosophers);
}

void	cleanup_philosophers(t_philosopher *philosophers)
{
	free(philosophers);
}

int	start_the_feast(t_philosopher *philosophers)
{
	printf("%d\n", philosophers[0].id);
	return (1);
}
