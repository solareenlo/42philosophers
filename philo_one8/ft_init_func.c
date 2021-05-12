/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 05:15:59 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/13 02:49:55 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_init_args(t_arg *args, int argc, char *argv[])
{
	if (ft_check_arg(argc, argv))
		return (1);
	args->number_of_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]) * 1000;
	args->time_to_eat = ft_atoi(argv[3]) * 1000;
	args->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
	{
		args->number_of_times_each_philo_must_eat = ft_atoi(argv[5]);
		if (args->number_of_times_each_philo_must_eat == 0)
			return (1);
	}
	else
		args->number_of_times_each_philo_must_eat = 0;
	return (0);
}

int	_init_mutex(t_global *global, t_arg args)
{
	int	i;

	pthread_mutex_init(&global->m_message, NULL);
	pthread_mutex_init(&global->m_done, NULL);
	pthread_mutex_lock(&global->m_done);
	i = 0;
	while (i < args.number_of_philo)
	{
		pthread_mutex_init(&global->philos[i].mutex, NULL);
		pthread_mutex_init(&global->philos[i].m_eat, NULL);
		pthread_mutex_lock(&global->philos[i].m_eat);
		pthread_mutex_init(&global->m_forks[i], NULL);
		i++;
	}
	return (0);
}

int	ft_init_global(t_global *global, t_arg *args)
{
	int	i;

	global->args = args;
	global->philos = malloc(sizeof(t_philo) * args->number_of_philo);
	if (global->philos == NULL)
		return (1);
	global->m_forks = malloc(sizeof(pthread_mutex_t) * args->number_of_philo);
	if (global->m_forks == NULL)
	{
		free(global->philos);
		return (1);
	}
	i = 0;
	while (i < args->number_of_philo)
	{
		global->philos[i].pos = i;
		global->philos[i].left_fork = i;
		global->philos[i].right_fork = (i + 1) % args->number_of_philo;
		global->philos[i].global = global;
		i++;
	}
	_init_mutex(global, *args);
	return (0);
}
