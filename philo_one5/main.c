/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 03:50:49 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/11 14:34:20 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_set_monitor(t_monitor *monitor, t_philo *philos, t_arg *args)
{
	int	i;

	monitor->philos = philos;
	monitor->args = args;
	monitor->m_forks = malloc(sizeof(pthread_mutex_t) * args->number_of_philo);
	if (monitor->m_forks == NULL)
		return (1);
	i = 0;
	while (i < args->number_of_philo)
		pthread_mutex_init(&monitor->m_forks[i++], NULL);
	pthread_mutex_init(&monitor->m_message, NULL);
	pthread_mutex_init(&monitor->m_died, NULL);
	pthread_mutex_lock(&monitor->m_died);
	return (0);
}

int	ft_set_philos(t_philo *philos, t_arg *args)
{
	int	i;

	philos = malloc(sizeof(t_philo) * args->number_of_philo);
	if (philos == NULL)
		return (1);
	i = 0;
	while (i < args->number_of_philo)
	{
		philos[i].done = 0;
		philos[i].pos = i;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % args->number_of_philo;
		philos[i].cnt = 0;
		philos[i].args = args;
		pthread_mutex_init(&philos[i].mutex, NULL);
		pthread_mutex_init(&philos[i].m_eat, NULL);
		pthread_mutex_lock(&philos[i].m_eat);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_arg		args;
	t_philo		*philos;
	t_monitor	monitor;

	if (ft_set_args(&args, argc, argv))
		return (1);
	ft_put_args(args);
	philos = NULL;
	monitor.m_forks = NULL;
	if (ft_set_philos(philos, &args))
		return (ft_destory_free(args, &philos, &monitor)
				&& ft_put_err("error: fatal\n"));
	if (ft_set_monitor(&monitor, philos, &args))
		return (ft_destory_free(args, &philos, &monitor)
				&& ft_put_err("error: fatal\n"));
	return (0);
}
