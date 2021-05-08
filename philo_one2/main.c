/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 03:50:49 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/08 10:55:44 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	_set_malloc(t_philo **ph, pthread_mutex_t **forks, t_monitor *mon,
				t_arg args)
{
	*ph = ft_calloc(args.number_of_philo, sizeof(t_philo));
	if (*ph == NULL)
		return (1);
	*forks = malloc(sizeof(pthread_mutex_t) * args.number_of_philo);
	if (*forks == NULL)
		return (1);
	mon->m_died = malloc(sizeof(pthread_mutex_t) * args.number_of_philo);
	if (mon->m_died == NULL)
		return (1);
	if (args.number_of_times_each_philo_must_eat != -1)
	{
		mon->m_done = malloc(sizeof(pthread_mutex_t) * args.number_of_philo);
		if (mon->m_done == NULL)
			return (1);
	}
	return (0);
}

void	_init_mutexes(pthread_mutex_t *forks, t_monitor *mon, t_arg args)
{
	int	i;

	i = 0;
	while (i < args.number_of_philo)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < args.number_of_philo)
		pthread_mutex_init(&mon->m_died[i++], NULL);
	if (args.number_of_times_each_philo_must_eat != -1)
	{
		i = 0;
		while (i < args.number_of_philo)
			pthread_mutex_init(&mon->m_done[i++], NULL);
	}
	pthread_mutex_init(&mon->m_message, NULL);
}

void		_run_philos(t_philo *ph, pthread_mutex_t *forks, t_monitor *mon, t_arg *args)
{
	int	i;

	args->start_time = ft_time_get_usec();
	i = 0;
	while (i < args->number_of_philo)
	{
		ph[i].id = i + 1;
		ph[i].args = args;
		ph[i].right_fork = &forks[(i + i % 2) % args->number_of_philo];
		ph[i].left_fork = &forks[(i + !(i % 2)) % args->number_of_philo];
		ph[i].last_time = args->start_time;
		ph[i].m_died = &mon->m_died[i];
		if (args->number_of_times_each_philo_must_eat != -1)
			ph[i].m_done = &mon->m_done[i];
		ph[i].m_message = &mon->m_message;
		pthread_create(&ph[i].thread, NULL, &ft_dining_philo, &ph[i]);
		i++;
	}
	i = 0;
	while (i < args->number_of_philo)
		pthread_detach(ph[i++].thread);
}

void	_run_monitor(t_monitor *mon, t_philo *ph, t_arg *args)
{
	int	*id;

	mon->args = args;
	mon->philos = ph;
	pthread_create(&mon->thread, NULL, &ft_monitor_philos, mon);
	pthread_join(mon->thread, (void **)&id);
	pthread_mutex_lock(&mon->m_message);
	if (id)
		ft_put_status(ph, DIED);
}

int	main(int argc, char *argv[])
{
	t_arg			args;
	t_philo			*philos;
	t_monitor		monitor;
	pthread_mutex_t	*forks;

	if (ft_set_args(&args, argc, argv))
		return (1);
	if (_set_malloc(&philos, &forks, &monitor, args))
		return (1);
	_init_mutexes(forks, &monitor, args);
	_run_philos(philos, forks, &monitor, &args);
	_run_monitor(&monitor, philos, &args);
	free(philos);
	free(forks);
	free(monitor.m_died);
	if (args.number_of_times_each_philo_must_eat != -1)
		free(monitor.m_done);
	return (0);
}
