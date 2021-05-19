/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dining_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 00:41:20 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/19 16:02:39 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	_forks(t_philo *philo)
{
	if (sem_wait(philo->global->sem_forks) != 0)
		return (1);
	if (ph_put_message(philo, FORK))
		return (1);
	if (sem_wait(philo->global->sem_forks) != 0)
		return (1);
	if (ph_put_message(philo, FORK))
		return (1);
	return (0);
}

static int	_eat(t_philo *philo)
{
	if (sem_wait(philo->sem) != 0)
		return (1);
	philo->last_eat = ph_get_time_usec();
	philo->time_limit = philo->last_eat + philo->global->args->time_to_die;
	if (philo->global->args->number_of_times_each_philo_must_eat)
	{
		philo->eat_cnt++;
		if (philo->eat_cnt
			== philo->global->args->number_of_times_each_philo_must_eat)
			sem_post(philo->global->sem_eat_cnt);
	}
	if (sem_post(philo->sem) != 0)
		return (1);
	if (ph_put_message(philo, EAT))
		return (1);
	ph_usleep(philo->global->args->time_to_eat);
	return (0);
}

static int	_sleep(t_philo *philo)
{
	if (sem_post(philo->global->sem_forks) != 0)
		return (1);
	if (sem_post(philo->global->sem_forks) != 0)
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

void	*process_dining_philo(t_philo *philo)
{
	pthread_t	thread;

	philo->last_eat = ph_get_time_usec();
	philo->time_limit = philo->last_eat + philo->global->args->time_to_die;
	if (pthread_create(&thread, NULL, thread_monitor_death, (void *)philo) != 0)
		return (NULL);
	if (pthread_detach(thread) != 0)
		return (NULL);
	while (42)
	{
		if (philo->global->the_end == 1)
			exit(0);
		if (_forks(philo))
			exit(1);
		if (_eat(philo))
			exit(1);
		if (_sleep(philo))
			exit(1);
		if (_think(philo))
			exit(1);
	}
	return (NULL);
}
