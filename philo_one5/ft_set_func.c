/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 05:15:59 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/11 19:52:42 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_set_args(t_arg *args, int argc, char *argv[])
{
	if (ft_check_arg(argc, argv))
		return (1);
	args->number_of_philo = ft_atoi(argv[1]);
	args->time_to_die = (size_t)1000 * ft_atoi(argv[2]);
	args->time_to_eat = (size_t)1000 * ft_atoi(argv[3]);
	args->time_to_sleep = (size_t)1000 * ft_atoi(argv[4]);
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

int	ft_init_global(t_arg *args, t_global *global)
{
	int	i;

	global->args = args;
	global->m_forks = malloc(sizeof(pthread_mutex_t) * args->number_of_philo);
	if (global->m_forks == NULL)
		return (1);
	i = 0;
	while (i < args->number_of_philo)
		pthread_mutex_init(&global->m_forks[i++], NULL);
	pthread_mutex_init(&global->m_message, NULL);
	pthread_mutex_init(&global->m_died, NULL);
	pthread_mutex_lock(&global->m_died);
	return (0);
}

int	ft_init_philos(t_arg *args, t_global *global)
{
	int	i;

	global->m_forks = NULL;
	global->philos = malloc(sizeof(t_philo) * args->number_of_philo);
	if (global->philos == NULL)
		return (1);
	i = 0;
	while (i < args->number_of_philo)
	{
		global->philos[i].done = 0;
		global->philos[i].pos = i;
		global->philos[i].left_fork = i;
		global->philos[i].right_fork = (i + 1) % args->number_of_philo;
		global->philos[i].cnt = 0;
		global->philos[i].args = args;
		global->philos[i].global = global;
		pthread_mutex_init(&global->philos[i].mutex, NULL);
		pthread_mutex_init(&global->philos[i].m_eat, NULL);
		pthread_mutex_lock(&global->philos[i].m_eat);
		i++;
	}
	return (0);
}
