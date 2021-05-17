/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_dining_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 00:41:20 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/18 01:57:03 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->global->m_forks[philo->left_fork]) != 0)
		return (1);
	if (ph_put_message(philo, FORK))
		return (1);
	if (pthread_mutex_lock(&philo->global->m_forks[philo->right_fork]) != 0)
		return (1);
	if (ph_put_message(philo, FORK))
		return (1);
	return (0);
}

static int	_eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->m_time_limit) != 0)
		return (1);
	philo->last_eat = ph_get_time_usec();
	philo->time_limit = philo->last_eat + philo->global->args->time_to_die;
	if (pthread_mutex_unlock(&philo->m_time_limit) != 0)
		return (1);
	if (pthread_mutex_lock(&philo->m_eat_cnt) != 0)
		return (1);
	philo->eat_cnt++;
	if (ph_put_message(philo, EAT))
		return (1);
	if (pthread_mutex_unlock(&philo->m_eat_cnt) != 0)
		return (1);
	ph_usleep(philo->global->args->time_to_eat);
	return (0);
}

static int	_sleep(t_philo *philo)
{
	if (pthread_mutex_unlock(&philo->global->m_forks[philo->left_fork]) != 0)
		return (1);
	if (pthread_mutex_unlock(&philo->global->m_forks[philo->right_fork]) != 0)
		return (1);
	if (ph_put_message(philo, SLEEP))
		return (1);
	ph_usleep(philo->global->args->time_to_sleep);
	return (0);
}

static int	_think(t_philo *philo)
{
	if (ph_put_message(philo, THINK))
		return (1);
	return (0);
}

void	*thread_dining_philo(void *arg)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)arg;
	philo->last_eat = ph_get_time_usec();
	philo->time_limit = philo->last_eat + philo->global->args->time_to_die;
	if (pthread_create(&thread, NULL, thread_monitor_death, (void *)philo) != 0)
		return (NULL);
	if (pthread_detach(thread) != 0)
		return (NULL);
	while (42)
	{
		if (philo->global->done == 1)
			return (NULL);
		if (_forks(philo))
			return (NULL);
		if (_eat(philo))
			return (NULL);
		if (_sleep(philo))
			return (NULL);
		if (_think(philo))
			return (NULL);
	}
	return (NULL);
}
