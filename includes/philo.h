/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:20:08 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/09 08:35:16 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>

# define BAD_INPUT "usage: number_of_philosopher, time_to_die, time_to_eat, \
time_to_sleep, [number_of_times_each_philosopher_must_eat]"

typedef struct s_global
{
	bool			death;
	int				nb;
	size_t			i;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			meal_to_eat;
	struct timeval	*time;
	struct s_philo	*philos;
	pthread_t		*wait_id;
	pthread_mutex_t	starter_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
}	t_global;

typedef struct s_philo
{
	int				id;
	int				meals;
	int				end;
	size_t			time_to_eat;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			last_eat;
	struct timeval	time_start;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	right_fork_mutex;
	t_global		*global;
}	t_philo;

//ARGS
int		args_traitment(int argc, char *argv[], t_global *global);
void	*routine(void *arg);
void	*monitoring(void *arg);
int		s_atoi(char *str, void *nb);

// mutex.c //
int		is_dead(t_global *global);
void	mutex_print(int nb, char *str, t_global *global);
void	print_msg(t_philo *philo);
int		starter(t_global *global, t_philo *philo);

// init.c //
int		init_starter_mutex(t_global *global);
int		init_print_mutex(t_global *global);
int		init_death_mutex(t_global *global);

// init2.c //
int		init_philo_struct(t_global *global);
int		init(t_global *global);

// manager.c //
void	custom_sleep(t_philo *philo, size_t action_time);
int		check_timer(t_philo *philo, size_t time_to_die);
int		check_each_philo(int *death, int *end, t_philo *philo);
size_t	gettime(struct timeval start);

// routine.c //
void	*only_one(void *arg);
#endif
