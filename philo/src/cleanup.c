/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:40:28 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/06 19:28:12 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(
	t_philosopher *philosophers,
	pthread_mutex_t *forks,
	t_args *args)
{
	free(forks);
	free(args);
	free(philosophers);
}
