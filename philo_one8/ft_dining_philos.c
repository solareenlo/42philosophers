/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dining_philos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 00:41:20 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/13 02:36:24 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	*_monitor_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (42)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->eating == 0 && ft_get_time_usec() > philo->time_limit)
		{
			ft_put_message(philo, DIED);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->global->m_done);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(1000);
	}
	return (NULL);
}

static void	_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->m_forks[philo->left_fork]);
	ft_put_message(philo, FORK);
	pthread_mutex_lock(&philo->global->m_forks[philo->right_fork]);
	ft_put_message(philo, FORK);
}

static void	_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->eating = 1;
	philo->last_eat = ft_get_time_usec();
	philo->time_limit = philo->last_eat + philo->global->args->time_to_die;
	ft_put_message(philo, EAT);
	ft_usleep(philo->global->args->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->m_eat);
}

static void	_sleep(t_philo *philo)
{
	pthread_mutex_unlock(&philo->global->m_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->global->m_forks[philo->right_fork]);
	ft_put_message(philo, SLEEP);
	ft_usleep(philo->global->args->time_to_sleep);
}

void	*ft_dining_philos(void *arg)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)arg;
	philo->last_eat = ft_get_time_usec();
	philo->time_limit = philo->last_eat + philo->global->args->time_to_die;
	pthread_create(&thread, NULL, &_monitor_philo, (void *)philo);
	pthread_detach(thread);
	while (42)
	{
		_take_forks(philo);
		_eat(philo);
		_sleep(philo);
		ft_put_message(philo, THINK);
	}
	return (NULL);
}
