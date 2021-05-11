/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dining_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:01:33 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/11 18:37:39 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void *_monitor_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (42)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->done == 0 && ft_get_time_msec() > philo->limit)
		{
			ft_put_message(philo, DIED);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->global->m_died);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mutex);
		ft_usleep(1000);
	}
}

void	_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->m_forks[philo->left_fork]);
	ft_put_message(philo, FORK);
	pthread_mutex_lock(&philo->global->m_forks[philo->right_fork]);
	ft_put_message(philo, FORK);
}

void	_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->done = 1;
	philo->last_eat = ft_get_time_msec();
	philo->limit = philo->last_eat + philo->args->time_to_die;
	ft_put_message(philo, EAT);
	ft_usleep(philo->args->time_to_eat);
	philo->cnt++;
	philo->done = 0;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->m_eat);
}

void	_drop_forks(t_philo *philo)
{
	ft_put_message(philo, SLEEP);
	pthread_mutex_unlock(&philo->global->m_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->global->m_forks[philo->right_fork]);
	ft_usleep(philo->args->time_to_sleep);
}

void	*ft_dining_philo(void *arg)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)arg;
	philo->last_eat = ft_get_time_msec();
	philo->limit = philo->last_eat + philo->args->time_to_die;
	if (pthread_create(&thread, NULL, &_monitor_philo, (void *)philo) != 0)
		return ((void *)1);
	pthread_detach(thread);
	while (42)
	{
		_take_forks(philo);
		_eat(philo);
		_drop_forks(philo);
		ft_put_message(philo, THINK);
	}
	return (NULL);
}
