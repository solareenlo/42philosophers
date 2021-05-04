/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:55:26 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/04 17:13:38 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_set_args(int argc, char *argv[], t_arg *args)
{
	if (ft_check_arg(argc, argv))
		return (1);
	memset(args, 0, sizeof(*args));
	args->number_of_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->number_ot_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		args->number_ot_times_each_philo_must_eat = -1;
	return (0);
}
