/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 05:15:59 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/11 12:41:48 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_set_args(t_arg *args, int argc, char *argv[])
{
	if (ft_check_arg(argc, argv))
		return (1);
	args->start_time = ft_time_get_usec();
	args->number_of_philo = ft_atoi(argv[1]);
	args->time_to_die = (size_t)1000 * ft_atoi(argv[2]);
	args->time_to_eat = (size_t)1000 * ft_atoi(argv[3]);
	args->time_to_sleep = (size_t)1000 * ft_atoi(argv[4]);
	if (argc == 6)
	{
		args->number_of_times_each_philo_must_eat = ft_atoi(argv[5]);
		if (args->number_of_times_each_philo_must_eat == 0)
			return (1);
	}
	else
		args->number_of_times_each_philo_must_eat = 0;
	return (0);
}
