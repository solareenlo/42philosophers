/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor_eat_cnt.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 11:29:37 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/19 16:01:15 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*thread_monitor_eat_cnt(void *arg)
{
	int			i;
	t_global	*global;

	global = (t_global *)arg;
	i = global->args->number_of_philo;
	while (i--)
		sem_wait(global->sem_eat_cnt);
	ph_put_message(&global->philos[0], DONE);
	sem_post(global->sem_done);
	return (NULL);
}
