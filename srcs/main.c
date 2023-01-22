/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:17:16 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/22 21:16:54 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo(t_global *global)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	pthread_mutex_lock(&global->starter_mutex);
	while (i < global->nb)
	{
		global->philos[i].last_eat = 0;
		if (pthread_create(&global->wait_id[i], \
		NULL, &routine, &global->philos[i]))
			return (0);
		i++;
	}
	pthread_mutex_unlock(&global->starter_mutex);
	i = 0;
	if (pthread_create(&monitor, NULL, &monitoring, global))
		return (0);
	pthread_join(monitor, NULL);
	while (i < global->nb)
	{
		pthread_join(global->wait_id[i], NULL);
		i++;
	}
	return (1);
}

int	clean(t_global *global)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&global->starter_mutex);
	pthread_mutex_destroy(&global->print_mutex);
	pthread_mutex_destroy(&global->death_mutex);
	while (i < global->nb)
	{
		pthread_mutex_destroy(&global->philos[i].right_fork_mutex);
		pthread_mutex_destroy(&global->philos[i].meal_mutex);
		i++;
	}
	free(global->wait_id);
	free(global->philos);
	return (1);
}

void	*only_one(void *arg)
{
	t_global	*global;

	global = arg;
	printf("0 1 has taken a fork\n");
	usleep(global->time_to_die);
	printf("%ld 1 died\n", global->time_to_die);
	return (NULL);
}

int	solo_routine(t_global *global)
{
	if (pthread_create(&global->wait_id[0], NULL, &only_one, global))
		return (0);
	pthread_join(global->wait_id[0], NULL);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_global	global;

	global.nb = 0;
	global.time_to_eat = 0;
	global.meal_to_eat = 0;
	global.time_to_die = 0;
	global.time_to_sleep = 0;
	global.death = 0;
	if (!args_traitment(argc, argv, &global))
		return (1);
	if (!init(&global))
		return (1);
	if (global.nb > 1)
	{
		if (!create_philo(&global))
			return (1);
	}
	else if (!solo_routine(&global))
		return (1);
	clean(&global);
	return (0);
}
