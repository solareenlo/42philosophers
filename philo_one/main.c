/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:21:57 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/07 05:52:59 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	_time_diff_msec(size_t time1, size_t time2)
{
	int	res;

	res = (time2 - time1) / 1000;
	return (res);
}

int	*_get_id_dead_philo(t_philo **philos)
{
	size_t	now;
	int		i;

	i = 0;
	while (i < philos[i]->args->number_of_philo)
	{
		if (pthread_mutex_lock(philos[i]->m_died) != 0)
			return (NULL);
		now = ft_get_time_usec();
		if (_time_diff_msec(philos[i]->args->start_time, now) >= philos[i]->args->time_to_die)
			return (&(philos[i]->id));
		if (pthread_mutex_unlock(philos[i]->m_died) != 0)
			return (NULL);
	}
	return (NULL);
}

void	*_monitor_philos(void *var)
{
	t_arg			*args;
	t_philo			**philos;
	t_monitor		monitor;
	void			*id;

	monitor = *(t_monitor *)var;
	args = monitor.args;
	philos = monitor.philos;
	while (42)
	{
		id = _get_id_dead_philo(philos);
		if (id)
			return (id);
	}
	return (NULL);
}

int	_run_monitor(t_monitor *monitor)
{
	void	*id;

	if (pthread_create(&monitor->thread, NULL, &_monitor_philos, monitor) != 0)
		return (1);
	if (pthread_join(monitor->thread, &id) != 0)
		return (1);
	if (pthread_mutex_lock(&monitor->m_message) != 0)
		return (1);
	if (id)
		ft_print_philo((monitor->philos)[*(int *)id - 1], DIED);
	if (pthread_mutex_unlock(&monitor->m_message) != 0)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_arg			args;
	pthread_mutex_t	*forks;
	t_philo			**philos;
	t_monitor		monitor;

	if (ft_set_args(&args, argc, argv))
		return (1);
	ft_putargs(args);
	if (ft_set_forks(&forks, args.number_of_philo))
		return (1);
	if (ft_set_philos(&philos, &args, forks))
		return (1);
	if (ft_set_monitor(&monitor, philos, &args))
		return (1);
	if (ft_run_philos(&philos, &monitor, args))
		return (1);
	if (_run_monitor(&monitor))
		return (1);
	free(forks);
	ft_free_philos(&philos, args.number_of_philo);
	return (0);
}
