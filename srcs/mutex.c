/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:32:26 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/22 21:39:46 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_global *global)
{
	pthread_mutex_lock(&global->death_mutex);
	if (global->death)
	{
		pthread_mutex_unlock(&global->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&global->death_mutex);
	return (0);
}

void	mutex_print(int id, char *str, t_global *global)
{
	pthread_mutex_lock(&global->print_mutex);
	if (!is_dead(global))
		printf("%ld %d %s\n", gettime(global->philos->time_start), id, str);
	pthread_mutex_unlock(&global->print_mutex);
}

void	print_msg(t_philo *philo)
{
	mutex_print(philo->id, "has taken a fork", philo->global);
	mutex_print(philo->id, "has taken a fork", philo->global);
	mutex_print(philo->id, "is eating", philo->global);
}

int	starter(t_global *global, t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(&philo->meal_mutex);
	meals = philo->meals;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&global->starter_mutex);
	pthread_mutex_unlock(&global->starter_mutex);
	return (meals);
}
