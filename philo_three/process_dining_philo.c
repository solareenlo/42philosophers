/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dining_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 00:41:20 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/21 02:15:30 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	_fork(t_philo *philo)
{
	if (sem_wait(philo->global->sem_forks) != 0)
		return (0);
	if (ph_put_message(philo, FORK))
		return (0);
	if (sem_wait(philo->global->sem_forks) != 0)
		return (0);
	if (ph_put_message(philo, FORK))
		return (0);
	philo->type = EAT;
	return (philo->alive);
}

static int	_eat(t_philo *philo)
{
	if (sem_wait(philo->sem) != 0)
		return (0);
	philo->last_eat = ph_get_time_usec();
	philo->time_limit = philo->last_eat + philo->global->args.time_to_die;
	if (sem_post(philo->sem) != 0)
		return (0);
	if (ph_put_message(philo, EAT))
		return (0);
	ph_usleep(philo->global->args.time_to_eat);
	if (sem_post(philo->global->sem_forks) != 0)
		return (0);
	if (sem_post(philo->global->sem_forks) != 0)
		return (0);
	if (philo->global->args.number_of_times_each_philo_must_eat)
	{
		philo->eat_cnt++;
		if (philo->eat_cnt
			== philo->global->args.number_of_times_each_philo_must_eat)
			return (0);
	}
	philo->type = SLEEP;
	return (philo->alive);
}

static int	_sleep(t_philo *philo)
{
	if (ph_put_message(philo, SLEEP))
		return (0);
	ph_usleep(philo->global->args.time_to_sleep);
	philo->type = THINK;
	return (philo->alive);
}

static int	_think(t_philo *philo)
{
	if (ph_put_message(philo, THINK))
		return (0);
	philo->type = FORK;
	return (philo->alive);
}

int	process_dining_philo(t_philo *philo)
{
	static t_func	process[4] = {_fork, _eat, _sleep, _think};
	pthread_t		thread;

	philo->last_eat = ph_get_time_usec();
	philo->time_limit = philo->last_eat + philo->global->args.time_to_die;
	if (pthread_create(&thread, NULL, thread_monitor_death, (void *)(philo))
		!= 0)
		return (1);
	if (pthread_detach(thread) != 0)
		return (1);
	while (42)
	{
		if (process[philo->type](philo) == 0)
			break ;
	}
	return (0);
}
