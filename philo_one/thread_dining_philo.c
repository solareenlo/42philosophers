/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_dining_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 00:41:20 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/17 02:41:02 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	*_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->m_someone_is_dead);
	if (philo->global->someone_is_dead == 1)
		return (NULL);
	pthread_mutex_unlock(&philo->global->m_someone_is_dead);
	pthread_mutex_lock(&philo->global->m_forks[philo->left_fork]);
	ph_put_message(philo, FORK);
	pthread_mutex_lock(&philo->global->m_someone_is_dead);
	if (philo->global->someone_is_dead == 1)
		return (NULL);
	pthread_mutex_unlock(&philo->global->m_someone_is_dead);
	pthread_mutex_lock(&philo->global->m_forks[philo->right_fork]);
	ph_put_message(philo, FORK);
	return (philo);
}

static void	*_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->m_someone_is_dead);
	if (philo->global->someone_is_dead == 1)
		return (NULL);
	pthread_mutex_unlock(&philo->global->m_someone_is_dead);
	pthread_mutex_lock(&philo->m_time_limit);
	philo->last_eat = ph_get_time_usec();
	philo->time_limit = philo->last_eat + philo->global->args->time_to_die;
	pthread_mutex_unlock(&philo->m_time_limit);
	pthread_mutex_lock(&philo->m_eat_cnt);
	philo->eat_cnt++;
	ph_put_message(philo, EAT);
	pthread_mutex_unlock(&philo->m_eat_cnt);
	ph_usleep(philo->global->args->time_to_eat);
	return (philo);
}

static void	*_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->m_someone_is_dead);
	if (philo->global->someone_is_dead == 1)
		return (NULL);
	pthread_mutex_unlock(&philo->global->m_someone_is_dead);
	pthread_mutex_unlock(&philo->global->m_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->global->m_forks[philo->right_fork]);
	ph_put_message(philo, SLEEP);
	ph_usleep(philo->global->args->time_to_sleep);
	return (philo);
}

static void	*_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->m_someone_is_dead);
	if (philo->global->someone_is_dead == 1)
		return (NULL);
	pthread_mutex_unlock(&philo->global->m_someone_is_dead);
	ph_put_message(philo, THINK);
	return (philo);
}

void	*thread_dining_philo(void *arg)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)arg;
	philo->last_eat = ph_get_time_usec();
	philo->time_limit = philo->last_eat + philo->global->args->time_to_die;
	pthread_create(&thread, NULL, thread_monitor_death, (void *)philo);
	pthread_detach(thread);
	while (42)
	{
		if (_forks(philo) == NULL)
			return (NULL);
		if (_eat(philo) == NULL)
			return (NULL);
		if (_sleep(philo) == NULL)
			return (NULL);
		if (_think(philo) == NULL)
			return (NULL);
	}
	return (NULL);
}
