/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:40:28 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/08 20:50:13 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(
	t_philosopher *philosophers,
	pthread_mutex_t *forks,
	t_args *args)
{
	free_forks(forks, args->philo_count);
	free_philosophers(philosophers);
	free(args);
}
