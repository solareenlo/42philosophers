/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 09:30:00 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/13 20:27:50 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

size_t	ft_get_time_usec(void)
{
	struct timeval	tv;
	size_t			res;

	gettimeofday(&tv, NULL);
	res = 0;
	res += tv.tv_sec * 1000000;
	res += tv.tv_usec;
	return (res);
}

size_t	ft_get_time_msec(void)
{
	struct timeval	tv;
	size_t			res;

	gettimeofday(&tv, NULL);
	res = 0;
	res += tv.tv_sec * 1000;
	res += tv.tv_usec / 1000;
	return (res);
}

void	ft_usleep(size_t sleep)
{
	size_t	stop;

	stop = ft_get_time_usec() + sleep;
	while (ft_get_time_usec() < stop)
		usleep(100);
}