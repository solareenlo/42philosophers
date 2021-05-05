/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 02:57:20 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/06 03:00:40 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

pthread_mutex_t	*ft_init_mutex(int n)
{
	pthread_mutex_t	*res;
	int				i;

	res = ft_calloc(n, sizeof(pthread_mutex_t));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&res[i], NULL);
		i++;
	}
	return (res);
}
