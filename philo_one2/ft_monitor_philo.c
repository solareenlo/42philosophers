/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:38:50 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/08 10:50:23 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	*check_starvation(t_philo *ph, t_arg *args)
{
	size_t	time_diff;
	int		i;
	size_t	now;

	i = 0;
	while (i < args->number_of_philo)
	{
		now = ft_time_get_usec();
		pthread_mutex_lock(ph[i].m_died);
		time_diff = ft_time_diff_usec(ph[i].last_time, now);
		if (time_diff >= ph[i].args->time_to_die)
			return (&ph[i].id);
		pthread_mutex_unlock(ph[i].m_died);
		i++;
	}
	return (NULL);
}

int	is_dining_complete(t_philo *ph, t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philo)
	{
		pthread_mutex_lock(ph[i].m_done);
		if (ph[i].done == 0)
		{
			pthread_mutex_unlock(ph[i].m_done);
			return (0);
		}
		pthread_mutex_unlock(ph[i].m_done);
		i++;
	}
	return (1);
}

void	*ft_monitor_philos(void *vars)
{
	t_arg		*args;
	t_philo		*ph;
	t_monitor	*mon;
	int			*id;

	mon = vars;
	ph = mon->philos;
	args = mon->args;
	while (42)
	{
		id = check_starvation(ph, args);
		if (id)
			return ((void *)id);
		if (args->number_of_times_each_philo_must_eat != -1)
			if (is_dining_complete(ph, args))
				return (NULL);
		ft_time_usleep(5000);
	}
	return (NULL);
}
