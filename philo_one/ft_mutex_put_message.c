/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex_put_message.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 04:56:12 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/07 05:02:19 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ft_mutex_put_message(t_philo *philo, int status)
{
	if (status == EAT)
	{
		if (pthread_mutex_lock(philo->m_message) != 0)
			return (NULL);
		ft_print_philo(philo, status);
		usleep(philo->args->time_to_eat);
		if (pthread_mutex_unlock(philo->m_message) != 0)
			return (NULL);
	}
	else if (status == SLEEP)
	{
		if (pthread_mutex_lock(philo->m_message) != 0)
			return (NULL);
		ft_print_philo(philo, status);
		usleep(philo->args->time_to_sleep);
		if (pthread_mutex_unlock(philo->m_message) != 0)
			return (NULL);
	}
	else
	{
		if (pthread_mutex_lock(philo->m_message) != 0)
			return (NULL);
		ft_print_philo(philo, status);
		if (pthread_mutex_unlock(philo->m_message) != 0)
			return (NULL);
	}
	return (philo);
}
