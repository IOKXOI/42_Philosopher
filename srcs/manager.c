/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:21:36 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/22 18:26:54 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_timer(t_philo *philo, size_t time_to_die)
{
	size_t	last_eat;

	pthread_mutex_lock(&philo->last_eat_mutex);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(&philo->last_eat_mutex);
	if (gettime(philo->time_start) > last_eat + time_to_die)
	{
		mutex_print(philo->id, "died", philo->global);
		return (1);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	if (!philo->meals)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

size_t	gettime(struct timeval start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return ((1e3 * ((&end)->tv_sec - (&start)->tv_sec)) \
	+ (1e-3 * ((&end)->tv_usec - (&start)->tv_usec)));
}

size_t	actual_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	custom_sleep(t_philo *philo, size_t to_sleep)
{
	size_t	start;

	start = actual_time();
	while ((actual_time() - start) < to_sleep && !is_dead(philo->global))
		usleep(1000);
}

int	check_each_philo(int *death, int *end, t_philo *philo)
{
	*death = check_timer(philo, philo->global->time_to_die);
	if (*death == -1)
	{
		*death = 0;
		philo->end = 1;
		(*end)--;
		if (*end == 0)
			return (0);
	}
	return (1);
}
