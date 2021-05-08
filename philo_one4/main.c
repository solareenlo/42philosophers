/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 03:50:49 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/08 12:18:17 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	_set_malloc(t_philo **ph, pthread_mutex_t **forks, t_monitor *mon, t_args *args)
{
	*ph = malloc(sizeof(t_philo) * args->number_of_philo);
	if (*ph == NULL)
		return (-1);
	memset(*ph, 0, sizeof(t_philo) * args->number_of_philo);
	*forks = malloc(sizeof(pthread_mutex_t) * args->number_of_philo);
	if (*forks == NULL)
		return (-1);
	mon->check_starvation = malloc(sizeof(pthread_mutex_t) * args->number_of_philo);
	if (mon->check_starvation == NULL)
		return (-1);
	if (args->limit_times_to_eat)
	{
		mon->check_dining_complete = malloc(sizeof(pthread_mutex_t) * args->number_of_philo);
		if (mon->check_dining_complete == NULL)
			return (-1);
	}
	return (0);
}

void	_init_mutexes(pthread_mutex_t *forks, t_monitor *mon, t_args *args)
{
	unsigned	i;

	i = 0;
	while (i < args->number_of_philo)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < args->number_of_philo)
		pthread_mutex_init(&mon->check_starvation[i++], NULL);
	if (args->limit_times_to_eat)
	{
		i = 0;
		while (i < args->number_of_philo)
			pthread_mutex_init(&mon->check_dining_complete[i++], NULL);
	}
	pthread_mutex_init(&mon->print_status, NULL);
}

void	_run_philos(t_philo *ph, pthread_mutex_t *forks, t_monitor *mon, t_args *args)
{
	unsigned	i;

	args->start_time = ft_time_get_usec();
	i = 0;
	while (i < args->number_of_philo)
	{
		ph[i].id = i + 1;
		ph[i].args = args;
		ph[i].first_fork = &forks[(i + i % 2) % args->number_of_philo];
		ph[i].second_fork = &forks[(i + !(i % 2)) % args->number_of_philo];
		ph[i].last_eat_time = args->start_time;
		ph[i].check_starvation = &mon->check_starvation[i];
		if (args->limit_times_to_eat)
			ph[i].check_dining_complete = &mon->check_dining_complete[i];
		ph[i].print_status = &mon->print_status;
		pthread_create(&ph[i].thread, NULL, &ft_dining_philo, &ph[i]);
		i++;
	}
	i = 0;
	while (i < args->number_of_philo)
		pthread_detach(ph[i++].thread);
}

void	_run_monitor(t_monitor *mon, t_philo *ph, t_args *args)
{
	unsigned		*id;

	mon->args = args;
	mon->ph = ph;
	pthread_create(&mon->thread, NULL, &ft_monitor_philos, mon);
	pthread_join(mon->thread, (void **)&id);
	if (id)
		ft_put_message(ph, DIED);
}

int	main(int argc, char *argv[])
{
	t_args			args;
	t_monitor		mon;
	t_philo			*ph;
	pthread_mutex_t	*forks;

	memset(&args, 0, sizeof(args));
	memset(&mon, 0, sizeof(mon));
	if (ft_set_args(&args, argc, argv))
		return (1);
	if (_set_malloc(&ph, &forks, &mon, &args) == -1)
		return (1);
	_init_mutexes(forks, &mon, &args);
	_run_philos(ph, forks, &mon, &args);
	_run_monitor(&mon, ph, &args);
	free(ph);
	free(forks);
	free(mon.check_starvation);
	if (args.limit_times_to_eat)
		free(mon.check_dining_complete);
	return (0);
}
