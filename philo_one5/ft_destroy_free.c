/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:03:40 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/11 19:56:28 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_destory_free(t_arg args, t_global *global)
{
	int	i;

	if (global->philos != NULL)
	{
		i = 0;
		while (i < args.number_of_philo)
		{
			pthread_mutex_destroy(&global->philos[i].mutex);
			pthread_mutex_destroy(&global->philos[i].m_eat);
			i++;
		}
		free(global->philos);
	}
	if (global->m_forks != NULL)
	{
		i = 0;
		while (i < args.number_of_philo)
			pthread_mutex_destroy(&global->m_forks[i++]);
		free(global->m_forks);
		pthread_mutex_destroy(&global->m_message);
		pthread_mutex_destroy(&global->m_died);
	}
	return (1);
}
