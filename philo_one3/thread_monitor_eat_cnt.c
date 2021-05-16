/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor_eat_cnt.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 11:29:37 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/16 14:14:37 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	_is_full(t_global *global, int *cnt)
{
	int	i;

	i = 0;
	while (i < global->args->number_of_philo)
	{
		pthread_mutex_lock(&global->philos[i].m_eat_cnt);
		if (global->philos[i].eat_cnt
			>= global->args->number_of_times_each_philo_must_eat)
		{
			(*cnt)++;
			global->philos[i].eat_cnt = -INTMAX;
		}
		pthread_mutex_unlock(&global->philos[i].m_eat_cnt);
		i++;
	}
}

void	*thread_monitor_eat_cnt(void *arg)
{
	t_global	*global;
	int			cnt;

	global = (t_global *)arg;
	cnt = 0;
	while (42)
	{
		pthread_mutex_lock(&global->m_someone_is_deat);
		if (global->someone_is_dead == 1)
			return (NULL);
		pthread_mutex_unlock(&global->m_someone_is_deat);
		if (cnt == global->args->number_of_philo)
			break ;
		_is_full(global, &cnt);
	}
	ft_put_message(&global->philos[0], DONE);
	pthread_mutex_unlock(&global->m_done);
	return (NULL);
}
