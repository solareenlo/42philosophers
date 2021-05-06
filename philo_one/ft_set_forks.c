/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 03:06:45 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/06 03:13:59 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_set_forks(pthread_mutex_t **forks, int n)
{
	*forks = ft_init_mutex(n);
	if (forks == NULL)
		return (1);
	return (0);
}
