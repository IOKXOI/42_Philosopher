/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:48:26 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/21 18:20:07 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_starter_mutex(t_global *global)
{
	if (pthread_mutex_init(&global->starter_mutex, NULL))
		return (0);
	return (1);
}

int	init_print_mutex(t_global *global)
{
	if (pthread_mutex_init(&global->print_mutex, NULL))
		return (0);
	return (1);
}

int	init_death_mutex(t_global *global)
{
	if (pthread_mutex_init(&global->death_mutex, NULL))
		return (0);
	return (1);
}
