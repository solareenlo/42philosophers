/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor_death.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:57:06 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/18 08:50:06 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*thread_monitor_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (42)
	{
		if (philo->global->done == 1)
			return (NULL);
		if (sem_wait(philo->sem_time_limit) != 0)
			break ;
		if (ph_get_time_usec() > philo->time_limit)
		{
			ph_put_message(philo, DIED);
			sem_post(philo->sem_time_limit);
			sem_post(philo->global->sem_done);
			return (NULL);
		}
		if (sem_post(philo->sem_time_limit) != 0)
			break ;
		usleep(ONECYCLE);
	}
	return (NULL);
}
