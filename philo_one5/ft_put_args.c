/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 04:01:38 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/11 13:39:36 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_put_args(t_arg args)
{
	printf("%d\n", args.number_of_philo);
	printf("%zu\n", args.time_to_die);
	printf("%zu\n", args.time_to_eat);
	printf("%zu\n", args.time_to_sleep);
	if (args.number_of_times_each_philo_must_eat != 0)
		printf("%zu\n", args.number_of_times_each_philo_must_eat);
}
