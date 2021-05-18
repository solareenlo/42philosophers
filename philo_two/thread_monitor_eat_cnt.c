/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor_eat_cnt.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 11:29:37 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/18 13:40:25 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	_is_full(t_global *global, int *cnt)
{
	int	i;

	i = 0;
	while (i < global->args->number_of_philo)
	{
		if (sem_wait(global->philos[i].sem) != 0)
			return (1);
		if (global->philos[i].eat_cnt
			>= global->args->number_of_times_each_philo_must_eat)
		{
			(*cnt)++;
			global->philos[i].eat_cnt = -INTMAX;
		}
		if (sem_post(global->philos[i].sem) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	*thread_monitor_eat_cnt(void *arg)
{
	t_global	*global;
	int			cnt;

	global = (t_global *)arg;
	cnt = 0;
	while (42)
	{
		if (cnt == global->args->number_of_philo)
			break ;
		if (global->done == 1)
			return (NULL);
		if (_is_full(global, &cnt))
		{
			sem_post(global->sem_done);
			return (NULL);
		}
	}
	ph_put_message(&global->philos[0], DONE);
	sem_post(global->sem_done);
	return (NULL);
}
