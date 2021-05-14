/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dining_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 00:41:20 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/14 23:21:22 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->m_forks[philo->left_fork]);
	ft_put_message(philo, FORK);
	pthread_mutex_lock(&philo->global->m_forks[philo->right_fork]);
	ft_put_message(philo, FORK);
}

static void	_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_limit_time);
	philo->last_eat = ft_get_time_usec();
	philo->time_limit = philo->last_eat + philo->global->args->time_to_die;
	pthread_mutex_lock(&philo->m_eat_cnt);
	philo->eat_cnt++;
	ft_put_message(philo, EAT);
	pthread_mutex_unlock(&philo->m_eat_cnt);
	pthread_mutex_unlock(&philo->m_limit_time);
	ft_usleep(philo->global->args->time_to_eat);
	pthread_mutex_unlock(&philo->m_eat);
}

static void	_sleep(t_philo *philo)
{
	pthread_mutex_unlock(&philo->global->m_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->global->m_forks[philo->right_fork]);
	ft_put_message(philo, SLEEP);
	ft_usleep(philo->global->args->time_to_sleep);
}

void	*ft_dining_philo(void *arg)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->m_limit_time);
	philo->last_eat = ft_get_time_usec();
	philo->time_limit = philo->last_eat + philo->global->args->time_to_die;
	pthread_mutex_unlock(&philo->m_limit_time);
	pthread_create(&thread, NULL, ft_monitor_philo, (void *)philo);
	pthread_detach(thread);
	while (42)
	{
		pthread_mutex_lock(&philo->m_status);
		if (philo->status != ALIVE)
		{
			pthread_mutex_unlock(&philo->m_status);
			break ;
		}
		pthread_mutex_unlock(&philo->m_status);
		pthread_mutex_lock(&philo->global->m_someone_is_deat);
		if (philo->global->someone_is_dead == 1)
			return (NULL);
		pthread_mutex_unlock(&philo->global->m_someone_is_deat);
		_forks(philo);
		pthread_mutex_lock(&philo->global->m_someone_is_deat);
		if (philo->global->someone_is_dead == 1)
			return (NULL);
		pthread_mutex_unlock(&philo->global->m_someone_is_deat);
		_eat(philo);
		pthread_mutex_lock(&philo->global->m_someone_is_deat);
		if (philo->global->someone_is_dead == 1)
			return (NULL);
		pthread_mutex_unlock(&philo->global->m_someone_is_deat);
		_sleep(philo);
		pthread_mutex_lock(&philo->global->m_someone_is_deat);
		if (philo->global->someone_is_dead == 1)
			return (NULL);
		pthread_mutex_unlock(&philo->global->m_someone_is_deat);
		ft_put_message(philo, THINK);
		pthread_mutex_lock(&philo->global->m_someone_is_deat);
		if (philo->global->someone_is_dead == 1)
			return (NULL);
		pthread_mutex_unlock(&philo->global->m_someone_is_deat);
	}
	return (NULL);
}
