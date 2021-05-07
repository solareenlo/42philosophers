/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:45:10 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/07 21:28:41 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_run_philos(t_philo ***philos, t_monitor *monitor, t_arg args)
{
	int	i;

	i = 0;
	while (i < args.number_of_philo)
	{
		(*philos)[i]->m_message = &(monitor->m_message);
		(*philos)[i]->m_died = monitor->m_died;
		(*philos)[i]->m_done = monitor->m_done;
		if (pthread_create(&((*philos)[i]->thread), NULL, &ft_dining_philo,
			(void *)(*philos)[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < args.number_of_philo)
	{
		if (pthread_detach((*philos)[i]->thread) != 0)
			return (1);
		i++;
	}
	return (0);
}
