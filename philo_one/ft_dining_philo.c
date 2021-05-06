/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dining_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:52:31 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/06 19:22:30 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	*_eating(t_philo *philo)
{
	size_t	now;

	if (pthread_mutex_lock(philo->m_message) != 0)
		return (NULL);
	now = ft_get_time_usec();
	printf("%ld %d is eating\n", now - philo->args->start_time, philo->id);
	usleep(philo->args->time_to_eat);
	if (pthread_mutex_unlock(philo->m_message) != 0)
		return (NULL);
	return (philo);
}

static void	*_sleeping(t_philo *philo)
{
	size_t	now;

	if (pthread_mutex_lock(philo->m_message) != 0)
		return (NULL);
	now = ft_get_time_usec();
	printf("%ld %d is sleeping\n", now - philo->args->start_time, philo->id);
	usleep(philo->args->time_to_sleep);
	if (pthread_mutex_unlock(philo->m_message) != 0)
		return (NULL);
	return (philo);
}

static void	*_thinking(t_philo *philo)
{
	size_t	now;

	if (pthread_mutex_lock(philo->m_message) != 0)
		return (NULL);
	now = ft_get_time_usec();
	printf("%ld %d is thinking\n", now - philo->args->start_time, philo->id);
	if (pthread_mutex_unlock(philo->m_message) != 0)
		return (NULL);
	return (philo);
}

void	*ft_dining_philo(void *var)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)var;
	i = 0;
	while (42)
	{
		if (i > 0)
			break ;
		_eating(philo);
		_sleeping(philo);
		_thinking(philo);
		i++;
	}
	return (NULL);
}
