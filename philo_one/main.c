/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:21:57 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/07 04:14:59 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*_monitor_philos(void *var)
{
	t_arg			*args;
	t_philo			**philos;
	t_monitor		monitor;

	monitor = *(t_monitor *)var;
	args = monitor.args;
	philos = monitor.philos;
	return ((void *)(&(monitor.philos)[0]->id));
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
		ft_print_philo((monitor->philos)[0], DONE);
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
