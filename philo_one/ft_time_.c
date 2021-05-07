/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 09:30:00 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/07 22:10:11 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

size_t	ft_time_get_usec(void)
{
	struct timeval	tv;
	size_t			res;

	gettimeofday(&tv, NULL);
	res = 0;
	res += tv.tv_sec * 1000000;
	res += tv.tv_usec;
	return (res);
}

size_t	ft_time_diff_msec(size_t start, size_t end)
{
	size_t	res;

	res = (end - start) / 1000;
	return (res);
}

size_t	ft_time_diff_usec(size_t start, size_t end)
{
	size_t	res;

	res = (end - start);
	return (res);
}

void	ft_time_usleep(size_t sleep)
{
	size_t	stop;

	stop = ft_time_get_usec() + sleep;
	while (ft_time_get_usec() < stop)
		usleep(100);
}
