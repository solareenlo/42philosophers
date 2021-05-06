/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:22:40 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/06 17:07:32 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_set_monitor(t_monitor *monitor, t_philo **philos, t_arg *args)
{
	monitor->args = args;
	monitor->philos = philos;
	if (pthread_mutex_init(&(monitor->m_status), NULL) != 0)
		return (1);
	return (0);
}
