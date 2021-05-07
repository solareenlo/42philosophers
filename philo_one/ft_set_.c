/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 05:15:59 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/08 00:05:23 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static pthread_mutex_t	*_init_mutex(int n)
{
	pthread_mutex_t	*res;
	int				i;

	res = ft_calloc(n, sizeof(pthread_mutex_t));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&res[i], NULL) != 0)
		{
			free(res);
			return (NULL);
		}
		i++;
	}
	return (res);
}

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
		args->number_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		args->number_of_times_each_philo_must_eat = -1;
	return (0);
}

int	ft_set_forks(pthread_mutex_t **forks, int n)
{
	*forks = _init_mutex(n);
	if (forks == NULL)
		return (1);
	return (0);
}

int	ft_set_philos(t_philo ***philos, t_arg *args, pthread_mutex_t *forks)
{
	int	i;

	*philos = ft_calloc(args->number_of_philo, sizeof(t_philo *));
	if (*philos == NULL)
		return (ft_puterr_malloc());
	i = 0;
	while (i < args->number_of_philo)
	{
		(*philos)[i] = ft_calloc(1, sizeof(t_philo));
		if ((*philos)[i] == NULL)
		{
			ft_free_philos(philos, i + 1);
			return (ft_puterr_malloc());
		}
		(*philos)[i]->id = i + 1;
		(*philos)[i]->args = args;
		(*philos)[i]->last_time = args->start_time;
		(*philos)[i]->right_fork = &forks[i % args->number_of_philo];
		(*philos)[i]->left_fork = &forks[(i + 1) % args->number_of_philo];
		i++;
	}
	return (0);
}

int	ft_set_monitor(t_monitor *monitor, t_philo **philos, t_arg *args)
{
	monitor->args = args;
	monitor->philos = philos;
	if (pthread_mutex_init(&(monitor->m_message), NULL) != 0)
		return (1);
	monitor->m_died = _init_mutex(args->number_of_philo);
	if (monitor->m_died == NULL)
		return (1);
	monitor->m_done = _init_mutex(args->number_of_philo);
	if (monitor->m_done == NULL)
		return (1);
	return (0);
}
