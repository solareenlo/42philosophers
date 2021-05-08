/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 11:21:18 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/08 11:42:55 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_put_status(t_philo *philo, int status)
{
	size_t	now;
	size_t	start;
	int		diff;

	start = philo->args->start_time;
	now = ft_time_get_usec();
	diff = ft_time_diff_msec(start, now);
	if (status == DONE)
		printf("DONE!\n");
	else if (status == FORK)
		printf("%d %d has taken a fork\n", diff, philo->id);
	else if (status == EAT)
		printf("%d %d is eating\n", diff, philo->id);
	else if (status == SLEEP)
		printf("%d %d is sleeping\n", diff, philo->id);
	else if (status == THINK)
		printf("%d %d is thinking\n", diff, philo->id);
	else if (status == DIED)
		printf("%d %d is died\n", diff, philo->id);
}

void	ft_put_message(t_philo *philo, int status)
{
	if (status == EAT)
	{
		pthread_mutex_lock(philo->print_status);
		ft_put_status(philo, status);
		ft_time_usleep(philo->args->time_to_eat);
		pthread_mutex_unlock(philo->print_status);
	}
	else if (status == SLEEP)
	{
		pthread_mutex_lock(philo->print_status);
		ft_put_status(philo, status);
		pthread_mutex_unlock(philo->print_status);
		ft_time_usleep(philo->args->time_to_sleep);
	}
	else
	{
		pthread_mutex_lock(philo->print_status);
		ft_put_status(philo, status);
		pthread_mutex_unlock(philo->print_status);
	}
}
