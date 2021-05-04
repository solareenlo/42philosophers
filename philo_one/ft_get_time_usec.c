/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time_usec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:31:28 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/04 17:54:03 by tayamamo         ###   ########.fr       */
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
