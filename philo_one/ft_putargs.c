/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putargs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:10:43 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/04 17:16:11 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_putargs(t_arg args)
{
	printf("%d\n", args.number_of_philo);
	printf("%d\n", args.time_to_die);
	printf("%d\n", args.time_to_eat);
	printf("%d\n", args.time_to_sleep);
	if (args.number_ot_times_each_philo_must_eat != -1)
		printf("%d\n", args.number_ot_times_each_philo_must_eat);
}
