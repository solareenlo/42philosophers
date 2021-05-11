/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 05:15:59 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/11 14:35:20 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_set_args(t_arg *args, int argc, char *argv[])
{
	if (ft_check_arg(argc, argv))
		return (1);
	args->start_time = ft_time_get_usec();
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
