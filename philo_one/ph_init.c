/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 05:15:59 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/18 01:28:56 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ph_init_args(t_arg *args, int argc, char *argv[])
{
	if (ph_check_arg(argc, argv))
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

static int	_init_mutex(t_global *global, t_arg args)
{
	int	i;

	if (pthread_mutex_init(&global->m_message, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&global->m_done, NULL) != 0)
		return (1);
	if (pthread_mutex_lock(&global->m_done) != 0)
		return (1);
	i = 0;
	while (i < args.number_of_philo)
	{
		if (pthread_mutex_init(&global->philos[i].m_time_limit, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&global->philos[i].m_eat_cnt, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&global->m_forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

static void	_init_philos(t_global *global, t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philo)
	{
		global->philos[i].pos = i;
		global->philos[i].right_fork = i % args->number_of_philo;
		global->philos[i].left_fork = (i + 1) % args->number_of_philo;
		global->philos[i].eat_cnt = 0;
		global->philos[i].global = global;
		i++;
	}
}

int	ph_init_global(t_global *global, t_arg *args)
{
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
	global->done = 0;
	_init_philos(global, args);
	return (_init_mutex(global, *args));
}
