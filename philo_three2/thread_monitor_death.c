/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor_death.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:57:06 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/19 22:16:30 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*thread_monitor_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (42)
	{
		sem_wait(philo->global->sem_the_end);
		if (philo->global->the_end == 1)
		{
			ft_putstr_fd(RED, 1);
			ft_putstr_fd("The end!\n", 1);
			ft_putstr_fd(RESET, 1);
			sem_post(philo->global->sem_the_end);
			return (NULL);
		}
		sem_post(philo->global->sem_the_end);
		if (sem_wait(philo->sem) != 0)
			break ;
		if (ph_get_time_usec() > philo->time_limit)
		{
			ph_put_message(philo, DIED);
			sem_wait(philo->global->sem_the_end);
			philo->global->the_end = 1;
			sem_post(philo->global->sem_the_end);
			sem_post(philo->sem);
			sem_post(philo->global->sem_done);
			return (NULL);
		}
		if (sem_post(philo->sem) != 0)
			break ;
		usleep(ft_max(ONECYCLE,
				ONECYCLE * philo->global->args->number_of_philo / 100));
	}
	return (NULL);
}
