/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 08:38:54 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/22 21:15:09 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo_array(t_global *global)
{
	global->philos = malloc(sizeof(t_philo) * global->nb);
	if (!global->philos)
		return (0);
	return (1);
}

static int	init_storage_id(t_global *global)
{
	global->wait_id = malloc(sizeof(pthread_t) * global->nb);
	if (!global->wait_id)
		return (0);
	return (1);
}

static int	init_each_philo(int i, t_global *global)
{
	global->philos[i].id = i + 1;
	global->philos[i].meals = global->meal_to_eat;
	global->philos[i].end = 0;
	global->philos[i].time_to_eat = global->time_to_eat;
	global->philos[i].time_to_die = global->time_to_die;
	global->philos[i].time_to_sleep = global->time_to_sleep;
	global->philos[i].global = global;
	gettimeofday(&global->philos[i].time_start, NULL);
	if (pthread_mutex_init(&global->philos[i].last_eat_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&global->philos[i].meal_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&global->philos[i].right_fork_mutex, NULL))
		return (0);
	if (i > 0)
		global->philos[i].left_fork_mutex \
		= &global->philos[i - 1].right_fork_mutex;
	if (i == global->nb - 1)
		global->philos[0].left_fork_mutex = &global->philos[i].right_fork_mutex;
	return (1);
}

int	init_philo_struct(t_global *global)
{
	int		i;

	i = 0;
	while (i < global->nb)
	{
		if (!init_each_philo(i, global))
		{
			free(global->philos);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init(t_global *global)
{
	if (!init_starter_mutex(global))
		return (0);
	if (!init_print_mutex(global))
		return (0);
	if (!init_death_mutex(global))
		return (0);
	if (!init_philo_array(global))
		return (0);
	if (!init_philo_struct(global))
		return (0);
	if (!init_storage_id(global))
	{
		free(global->philos);
		return (0);
	}
	return (1);
}
