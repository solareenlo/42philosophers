/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_destroy_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 00:15:04 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/18 01:59:37 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	_destroy(t_global *global)
{
	int	ret;

	ret = 0;
	if (pthread_mutex_unlock(&global->m_message) != 0)
		ret++;
	if (pthread_mutex_destroy(&global->m_message) != 0)
		ret++;
	if (pthread_mutex_unlock(&global->m_done) != 0)
		ret++;
	if (pthread_mutex_destroy(&global->m_done) != 0)
		ret++;
	return (ret);
}

int	ph_destroy_free(t_global *global, t_arg args)
{
	int	i;
	int	ret;

	ret = _destroy(global);
	i = 0;
	while (i < args.number_of_philo)
	{
		if (pthread_mutex_unlock(&global->m_forks[i]) != 0)
			ret++;
		if (pthread_mutex_destroy(&global->m_forks[i]) != 0)
			ret++;
		if (pthread_mutex_unlock(&global->philos[i].m_time_limit) != 0)
			ret++;
		if (pthread_mutex_destroy(&global->philos[i].m_time_limit) != 0)
			ret++;
		if (pthread_mutex_unlock(&global->philos[i].m_eat_cnt) != 0)
			ret++;
		if (pthread_mutex_destroy(&global->philos[i].m_eat_cnt) != 0)
			ret++;
		i++;
	}
	free(global->philos);
	free(global->m_forks);
	return (ret);
}
