/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:08:26 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/12 22:18:10 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_free_destroy(t_global *global, t_arg *args)
{
	int	i;

	if (global->philos != NULL && global->m_forks != NULL)
	{
		pthread_mutex_destroy(&global->m_message);
		pthread_mutex_destroy(&global->m_picking);
	}
	if (global->philos != NULL)
	{
		i = 0;
		while (i < args->number_of_philo)
			pthread_mutex_destroy(&global->philos[i++].m_eating);
		free(global->philos);
	}
	if (global->m_forks != NULL)
	{
		i = 0;
		while (i < args->number_of_philo)
			pthread_mutex_destroy(&global->m_forks[i++]);
		free(global->m_forks);
	}
	return (1);
}

int	ft_put_err(const char *err)
{
	if (err)
		write(2, err, ft_strlen(err));
	return (1);
}
