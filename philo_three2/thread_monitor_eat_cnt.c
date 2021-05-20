/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor_eat_cnt.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 11:29:37 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/19 22:15:29 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	*_thread_monitor_eat_cnt(void *arg)
{
	int			i;
	t_global	*global;

	global = (t_global *)arg;
	i = global->args->number_of_philo;
	while (i--)
		sem_wait(global->sem_eat_cnt);
	ph_put_message(&global->philos[0], DONE);
	sem_wait(global->sem_the_end);
	global->the_end = 1;
	sem_post(global->sem_the_end);
	sem_post(global->sem_done);
	return (NULL);
}

int	thread_monitor_eat_cnt(t_global *global)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, _thread_monitor_eat_cnt,
			(void *)global) != 0)
		return (1);
	if (pthread_detach(thread) != 0)
		return (1);
	return (0);
}
