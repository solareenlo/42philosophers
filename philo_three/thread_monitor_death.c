/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor_death.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:57:06 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/19 14:52:35 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*thread_monitor_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (42)
	{
		/* sem_wait(philo->global->sem_the_end); */
		if (philo->global->the_end == 1)
		{
			/* sem_post(philo->global->sem_the_end); */
			return (NULL);
		}
		/* sem_post(philo->global->sem_the_end); */
		if (sem_wait(philo->sem) != 0)
			break ;
		if (ph_get_time_usec() > philo->time_limit)
		{
			ph_put_message(philo, DIED);
			sem_post(philo->sem);
			sem_post(philo->global->sem_done);
			return (NULL);
		}
		if (sem_post(philo->sem) != 0)
			break ;
		usleep(ONECYCLE);
	}
	return (NULL);
}
