/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:10:51 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/07 12:04:52 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initialization(
	char **argv,
	t_args **args,
	pthread_mutex_t **forks,
	t_philosopher **philosophers)
{
	*args = init_args(argv);
	if (*args == NULL)
		return (-1);
	*forks = init_forks((*args)->philo_count);
	if (!*forks)
		return (-1);
	*philosophers = init_philosophers(*args, *forks);
	if (!*philosophers)
		return (-1);
	return (0);
}
