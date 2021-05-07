/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putargs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:10:43 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/07 10:11:23 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_putargs(t_arg args)
{
	printf("%d\n", args.number_of_philo);
	printf("%zu\n", args.time_to_die);
	printf("%zu\n", args.time_to_eat);
	printf("%zu\n", args.time_to_sleep);
	if (args.number_of_times_each_philo_must_eat != -1)
		printf("%d\n", args.number_of_times_each_philo_must_eat);
}
