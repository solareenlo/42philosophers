/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dining_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 11:15:49 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/08 12:27:17 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	pickup_forks(t_philo *ph)
{
	pthread_mutex_lock(ph->first_fork);
	ft_put_message(ph, FORK);
	pthread_mutex_lock(ph->second_fork);
	ft_put_message(ph, FORK);
}

static void	increment_eat_count(t_philo *ph)
{
	ph->eat_count++;
	if ((int)ph->eat_count == ph->args->number_of_times_each_philo_must_eat)
	{
		pthread_mutex_lock(ph->check_dining_complete);
		ph->dining_complete = 1;
		pthread_mutex_unlock(ph->check_dining_complete);
	}
}

static void	eat_spaghetti(t_philo *ph)
{
	size_t	now;
	size_t	start;

	start = ph->args->start_time;
	now = ft_time_get_usec();
	pthread_mutex_lock(ph->check_starvation);
	ph->last_eat_time = now;
	pthread_mutex_unlock(ph->check_starvation);
	pthread_mutex_lock(ph->print_status);
	now = ft_time_get_usec();
	printf("%ld %d is eating\n", ft_time_diff_msec(start, now), ph->id);
	pthread_mutex_unlock(ph->print_status);
	ft_time_usleep(ph->args->time_to_eat);
	if (ph->args->limit_times_to_eat)
		increment_eat_count(ph);
	pthread_mutex_unlock(ph->second_fork);
	pthread_mutex_unlock(ph->first_fork);
}

void	*ft_dining_philo(void *vars)
{
	t_philo		*ph;

	ph = vars;
	while (42)
	{
		pickup_forks(ph);
		eat_spaghetti(ph);
		ft_put_message(ph, SLEEP);
		ft_put_message(ph, THINK);
		ft_time_usleep(1000);
	}
	return (NULL);
}
