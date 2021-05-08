/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 12:04:51 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/08 12:27:09 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

unsigned	*check_starvation(t_philo *ph, t_args *args)
{
	size_t		time_diff;
	unsigned	i;
	size_t		now;

	i = 0;
	while (i < args->number_of_philo)
	{
		now = ft_time_get_usec();
		pthread_mutex_lock(ph[i].check_starvation);
		time_diff = ft_time_diff_usec(ph[i].last_eat_time, now);
		if (time_diff >= ph[i].args->time_to_die)
			return (&ph[i].id);
		pthread_mutex_unlock(ph[i].check_starvation);
		i++;
	}
	return (NULL);
}

int	is_dining_complete(t_philo *ph, t_args *args)
{
	unsigned	i;

	i = 0;
	while (i < args->number_of_philo)
	{
		pthread_mutex_lock(ph[i].check_dining_complete);
		if (ph[i].dining_complete == 0)
		{
			pthread_mutex_unlock(ph[i].check_dining_complete);
			return (0);
		}
		pthread_mutex_unlock(ph[i].check_dining_complete);
		i++;
	}
	return (1);
}

void	*ft_monitor_philos(void *vars)
{
	t_args		*args;
	t_philo		*ph;
	t_monitor	*mon;
	unsigned	*id;

	mon = vars;
	ph = mon->ph;
	args = mon->args;
	while (42)
	{
		id = check_starvation(ph, args);
		if (id)
			return ((void *)id);
		if (args->limit_times_to_eat)
			if (is_dining_complete(ph, args))
				return (NULL);
		ft_time_usleep(5000);
	}
	return (NULL);
}
