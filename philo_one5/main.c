/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 03:50:49 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/11 14:35:16 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int argc, char *argv[])
{
	t_arg		args;
	t_philo		*philos;
	t_monitor	monitor;

	if (ft_set_args(&args, argc, argv))
		return (1);
	ft_put_args(args);
	philos = NULL;
	monitor.m_forks = NULL;
	if (ft_set_philos(philos, &args))
		return (ft_destory_free(args, &philos, &monitor)
				&& ft_put_err("error: fatal\n"));
	if (ft_set_monitor(&monitor, philos, &args))
		return (ft_destory_free(args, &philos, &monitor)
				&& ft_put_err("error: fatal\n"));
	return (0);
}
