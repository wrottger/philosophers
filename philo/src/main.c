/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:09:17 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/07 10:39:44 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philosopher	*philosophers;
	t_args			*args;
	pthread_mutex_t	*forks;

	(void)argc;
	args = NULL;
	forks = NULL;
	philosophers = NULL;
	if (initialization(argv, &args, &forks, &philosophers) == -1)
		return (1);
	start_the_feast(philosophers);
	cleanup(philosophers, forks, args);
	return (0);
}
