/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor_death.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:57:06 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/16 12:15:19 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	*_is_philo_died(t_philo *philo)
{
	if (ft_get_time_usec() > philo->time_limit)
	{
		pthread_mutex_lock(&philo->m_status);
		philo->status = DEAD;
		pthread_mutex_unlock(&philo->m_status);
		pthread_mutex_lock(&philo->global->m_someone_is_deat);
		philo->global->someone_is_dead = 1;
		pthread_mutex_unlock(&philo->global->m_someone_is_deat);
		ft_put_message(philo, DIED);
		pthread_mutex_unlock(&philo->m_time_limit);
		pthread_mutex_unlock(&philo->global->m_done);
		return (NULL);
	}
	return (philo);
}

void	*thread_monitor_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (42)
	{
		pthread_mutex_lock(&philo->m_status);
		if (philo->status != ALIVE)
		{
			pthread_mutex_unlock(&philo->m_status);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->m_status);
		pthread_mutex_lock(&philo->m_time_limit);
		if (_is_philo_died(philo) == NULL)
			return (NULL);
		pthread_mutex_unlock(&philo->m_time_limit);
		usleep(100);
	}
	return (NULL);
}
