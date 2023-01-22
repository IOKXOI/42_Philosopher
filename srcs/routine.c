/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:20:20 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/22 21:39:05 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_philo *philo)
{
	int	id;

	id = philo->id;
	if (!is_dead(philo->global))
	{
		if ((id - 1) % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork_mutex);
			pthread_mutex_lock(&philo->right_fork_mutex);
		}
		else
		{
			pthread_mutex_lock(&philo->right_fork_mutex);
			pthread_mutex_lock(philo->left_fork_mutex);
		}
		pthread_mutex_lock(&philo->last_eat_mutex);
		philo->last_eat = gettime(philo->time_start);
		pthread_mutex_unlock(&philo->last_eat_mutex);
		print_msg(philo);
		custom_sleep(philo, philo->time_to_eat);
		pthread_mutex_unlock(philo->left_fork_mutex);
		pthread_mutex_unlock(&philo->right_fork_mutex);
		return (1);
	}
	return (0);
}

static int	sleeping(t_philo *philo)
{
	if (!is_dead(philo->global))
	{
		mutex_print(philo->id, "is sleeping", philo->global);
		custom_sleep(philo, philo->time_to_sleep);
		return (1);
	}
	return (0);
}

static int	think(t_philo *philo)
{
	size_t	time_to_eat;
	size_t	time_to_sleep;

	time_to_eat = philo->time_to_eat;
	time_to_sleep = philo->time_to_sleep;
	if (!is_dead(philo->global))
	{
		mutex_print(philo->id, "is thinking", philo->global);
		if (philo->global->nb % 2 != 0 && time_to_eat >= time_to_sleep)
			usleep((time_to_eat - time_to_sleep) + 1000);
		return (1);
	}
	return (0);
}

void	*monitoring(void *arg)
{
	int			i;
	int			death;
	int			end;
	t_global	*global;

	death = 0;
	i = 0;
	global = arg;
	end = global->nb;
	while (!death)
	{
		if (!check_each_philo(&death, &end, &global->philos[i]))
			return (NULL);
		i++;
		if (i == global->nb)
			i = 0;
	}
	pthread_mutex_lock(&global->death_mutex);
	global->death = 1;
	pthread_mutex_unlock(&global->death_mutex);
	return (NULL);
}

void	*routine(void *arg)
{
	int			meals;
	t_philo		*philo;
	t_global	*global;

	philo = arg;
	global = philo->global;
	meals = starter(global, philo);
	if (philo->id % 2 == 0 || (philo->id % 2 != 0 && philo->id == global->nb))
		custom_sleep(philo, 50);
	while (!is_dead(global) && meals)
	{
		if (eat(philo))
		{
			pthread_mutex_lock(&philo->meal_mutex);
			meals = --philo->meals;
			pthread_mutex_unlock(&philo->meal_mutex);
			if (meals)
			{
				if (sleeping(philo))
					if (!think(philo))
						return (NULL);
			}
		}
	}
	return (NULL);
}
