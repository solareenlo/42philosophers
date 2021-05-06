/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 03:52:36 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/07 04:00:11 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_print_philo(t_philo *philo, int status)
{
	size_t	now;

	if (status == DONE)
	{
		printf("DONE!\n");
	}
	else if (status == FORK)
	{
		now = ft_get_time_usec();
		printf("%ld %d has taken a fork\n", now - philo->args->start_time, philo->id);
	}
	else if (status == EAT)
	{
		now = ft_get_time_usec();
		printf("%ld %d is eating\n", now - philo->args->start_time, philo->id);
	}
	else if (status == SLEEP)
	{
		now = ft_get_time_usec();
		printf("%ld %d is sleeping\n", now - philo->args->start_time, philo->id);
	}
	else if (status == THINK)
	{
		now = ft_get_time_usec();
		printf("%ld %d is thinking\n", now - philo->args->start_time, philo->id);
	}
	else if (status == DIED)
	{
		now = ft_get_time_usec();
		printf("%ld %d is died\n", now - philo->args->start_time, philo->id);
	}
}
