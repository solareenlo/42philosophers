/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor_death.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:57:06 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/18 01:18:21 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*thread_monitor_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (42)
	{
		if (philo->global->done == 1)
			return (NULL);
		pthread_mutex_lock(&philo->m_time_limit);
		if (ph_get_time_usec() > philo->time_limit)
		{
			ph_put_message(philo, DIED);
			pthread_mutex_unlock(&philo->m_time_limit);
			pthread_mutex_unlock(&philo->global->m_done);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->m_time_limit);
		usleep(ONECYCLE);
	}
	return (NULL);
}
