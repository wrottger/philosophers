/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:07:08 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/08 18:19:28 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_args(t_args *args)
{
	if (args->philo_count < 1)
	{
		printf("Error: Number of philosophers must be bigger than 0\n");
		return (-1);
	}
	if (args->time_to_die < 0
		|| args->time_to_eat < 0
		|| args->time_to_sleep < 0)
	{
		printf("Error: Arguments must be bigger than 0\n");
		return (-1);
	}
	return (0);
}

static int	argv_size(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

t_args	*init_args(char **argv)
{
	int		argc;
	t_args	*args;

	argc = argv_size(argv);
	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	memset(args, 0, sizeof(t_args));
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (NULL);
	}
	args->philo_count = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->must_eat_count = ft_atoi(argv[5]);
	else
		args->must_eat_count = -1;
	if (check_args(args) == -1)
		return (NULL);
	return (args);
}
