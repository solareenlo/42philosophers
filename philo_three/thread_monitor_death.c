/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor_death.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:57:06 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/21 01:59:29 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*thread_monitor_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (42)
	{
		if (sem_wait(philo->sem) != 0)
			break ;
		if (ph_get_time_usec() > philo->time_limit)
		{
			sem_wait(philo->global->sem_message);
			ft_putnbr_fd(ph_get_time_msec() - philo->global->start_time, 1);
			ft_putstr_fd("\t", 1);
			ft_putnbr_fd(philo->pos + 1, 1);
			ft_putstr_fd(RED, 1);
			ft_putstr_fd(" died\n", 1);
			ft_putstr_fd(RESET, 1);
			philo->alive = 0;
			sem_post(philo->sem);
			exit(1);
		}
		if (sem_post(philo->sem) != 0)
			break ;
		usleep(ONECYCLE);
	}
	return (NULL);
}
