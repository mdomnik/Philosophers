/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:51:47 by mdomnik           #+#    #+#             */
/*   Updated: 2024/07/03 16:29:12 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_args(t_args *args, char **argv)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	args->num_philo = ft_atoi_philo(argv[1], 0);
	args->time_to_die = ft_atoi_philo(argv[2], 0);
	args->time_to_eat = ft_atoi_philo(argv[3], 0);
	args->time_to_sleep = ft_atoi_philo(argv[4], 0);
	if (argv[5])
		args->num_eat = ft_atoi_philo(argv[5], 0);
	else
		args->num_eat = -1;
	args->philo_dead = 0;
	args->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	args->lowest_meal_count = 0;
	if (init_fork_locks(args) == 1)
		return (1);
	if (init_monitoring_thread(args) == 1)
		return (1);
	if (init_philo(args) == 1)
		return (1);
	return (0);
}

int	init_fork_locks(t_args *args)
{
	int	i;

	i = 0;
	args->fork_locks = 
		(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * args->num_philo);
	if (!args->fork_locks)
		error_philo(ERR_MALLOC);
	while (i < args->num_philo)
	{
		if (pthread_mutex_init(&args->fork_locks[i], NULL) != 0)
			error_philo(ERR_MUTEX_INIT);
		i++;
	}
	return (0);
}

int	init_monitoring_thread(t_args *args)
{
	if (pthread_mutex_init(&args->monitoring, NULL) != 0)
		error_philo(ERR_MUTEX_INIT);
	if (pthread_mutex_init(&args->philo_meal_mutex, NULL) != 0)
		error_philo(ERR_MUTEX_INIT);
	return (0);
}

int	init_philo(t_args *args)
{
	int	i;

	i = 0;
	args->philo = (t_philo *)malloc(sizeof(t_philo) * args->num_philo);
	if (!args->philo)
		error_philo(ERR_MALLOC);
	while (i < args->num_philo)
	{
		args->philo[i].philo_id = i + 1;
		args->philo[i].time_last_meal = 0;
		args->philo[i].is_eating = 0;
		args->philo[i].meals_count = 0;
		args->philo[i].local_philo_dead = 0;
		args->philo[i].local_lowest_meal = 0;
		args->philo[i].args = args;
		args->philo[i].left_fork = &args->fork_locks[i];
		args->philo[i].right_fork
			= &args->fork_locks[(i + 1) % args->num_philo];
		i++;
	}
	return (0);
}
