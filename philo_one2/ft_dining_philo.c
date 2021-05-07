/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dining_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 04:40:17 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/08 05:19:26 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	_think(t_philo *ph)
{
	ft_put_message(ph, THINK);
}

static void	_pickup_forks(t_philo *ph)
{
	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_lock(ph->m_message);
	ft_put_status(ph, FORK);
	pthread_mutex_unlock(ph->m_message);
	pthread_mutex_lock(ph->left_fork);
	pthread_mutex_lock(ph->m_message);
	ft_put_status(ph, FORK);
	pthread_mutex_unlock(ph->m_message);
}

void	increment_eat_count(t_philo *ph)
{
	ph->cnt++;
	if (ph->cnt == ph->args->number_of_times_each_philo_must_eat)
	{
		pthread_mutex_lock(ph->m_done);
		ph->done = 1;
		pthread_mutex_unlock(ph->m_done);
	}
}

void	_eat(t_philo *ph)
{
	size_t	now;
	size_t	start;

	start = ph->args->start_time;
	now = ft_time_get_usec();
	pthread_mutex_lock(ph->m_died);
	ph->last_time = now;
	pthread_mutex_unlock(ph->m_died);
	pthread_mutex_lock(ph->m_message);
	ft_put_status(ph, EAT);
	pthread_mutex_unlock(ph->m_message);
	ft_time_usleep(ph->args->time_to_eat);
	if (ph->args->number_of_times_each_philo_must_eat != -1)
		increment_eat_count(ph);
}

static void	_drop_forks(t_philo *ph)
{
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}

void	_sleep(t_philo *ph)
{
	ft_put_message(ph, SLEEP);
	ft_time_usleep(ph->args->time_to_sleep);
}

void		*ft_dining_philo(void *vars)
{
	t_philo			*ph;

	ph = (t_philo *)vars;
	/* _think(ph); */
	while (42)
	{
		_pickup_forks(ph);
		_eat(ph);
		_drop_forks(ph);
		_sleep(ph);
		_think(ph);
		ft_time_usleep(1000);
	}
	return (NULL);
}
