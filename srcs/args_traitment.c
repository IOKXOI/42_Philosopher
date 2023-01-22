/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_traitment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:22:48 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/09 08:40:01 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	argument_count(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf(BAD_INPUT);
		return (0);
	}
	return (1);
}

static int	parsing_argv(int argc, char *argv[], t_global *global)
{
	if (!s_atoi(argv[1], &global->nb)
		|| !s_atoi(argv[2], &global->time_to_die)
		|| !s_atoi(argv[3], &global->time_to_eat)
		|| !s_atoi(argv[4], &global->time_to_sleep))
	{
		printf("Input error\n");
		return (0);
	}
	if (global->nb < 1)
	{
		printf("No philosopher\n");
		return (0);
	}
	if (argc == 6)
	{
		if (!s_atoi(argv[5], &global->meal_to_eat))
		{
			printf("Input error\n");
			return (0);
		}
	}
	else
		global->meal_to_eat = -1;
	return (1);
}

int	args_traitment(int argc, char *argv[], t_global *global)
{
	if (!argument_count(argc))
		return (0);
	if (!parsing_argv(argc, argv, global))
		return (0);
	return (1);
}
