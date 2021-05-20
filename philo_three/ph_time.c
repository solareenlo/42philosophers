/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 09:30:00 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/18 17:31:48 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

size_t	ph_get_time_usec(void)
{
	struct timeval	tv;
	size_t			res;

	gettimeofday(&tv, NULL);
	res = 0;
	res += tv.tv_sec * 1000000;
	res += tv.tv_usec;
	return (res);
}

size_t	ph_get_time_msec(void)
{
	struct timeval	tv;
	size_t			res;

	gettimeofday(&tv, NULL);
	res = 0;
	res += tv.tv_sec * 1000;
	res += tv.tv_usec / 1000;
	return (res);
}

void	ph_usleep(size_t sleep)
{
	size_t	stop;

	stop = ph_get_time_usec() + sleep;
	while (ph_get_time_usec() < stop)
		usleep(100);
}
