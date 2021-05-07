/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 03:50:49 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/08 04:24:15 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	_set_malloc(t_philo **ph, pthread_mutex_t **forks, t_monitor *mon, t_arg args)
{
	*ph = malloc(sizeof(t_philo) * args.number_of_philo);
	if (*ph == NULL)
		return (0);
	memset(*ph, 0, sizeof(t_philo) * args.number_of_philo);
	*forks = malloc(sizeof(pthread_mutex_t) * args.number_of_philo);
	if (*forks == NULL)
		return (0);
	mon->m_died = malloc(sizeof(pthread_mutex_t) * args.number_of_philo);
	if (mon->m_died == NULL)
		return (0);
	if (args.number_of_times_each_philo_must_eat != -1)
	{
		mon->m_done = malloc(sizeof(pthread_mutex_t) * args.number_of_philo);
		if (mon->m_done == NULL)
			return (0);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_arg			args;
	t_philo			*philos;
	t_monitor		monitor;
	pthread_mutex_t	*forks;

	if (ft_set_args(&args, argc, argv))
		return (1);
	ft_put_args(args);
	_set_malloc(&philos, &forks, &monitor, args);
	free(philos);
	free(forks);
	return (0);
}
