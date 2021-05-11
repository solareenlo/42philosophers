/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:03:40 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/11 14:33:39 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_destory_free(t_arg args, t_philo **philos, t_monitor *monitor)
{
	int	i;

	if (*philos != NULL)
	{
		i = 0;
		while (i < args.number_of_philo)
		{
			pthread_mutex_destroy(&philos[i]->mutex);
			pthread_mutex_destroy(&philos[i]->m_eat);
			i++;
		}
		free(philos);
	}
	if (monitor->m_forks != NULL)
	{
		i = 0;
		while (i < args.number_of_philo)
			pthread_mutex_destroy(&monitor->m_forks[i++]);
		free(monitor->m_forks);
		pthread_mutex_destroy(&monitor->m_message);
		pthread_mutex_destroy(&monitor->m_died);
	}
	return (1);
}
