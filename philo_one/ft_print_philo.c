/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 03:52:36 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/07 09:45:16 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_print_philo(t_philo *philo, int status)
{
	size_t	now;
	size_t	start;
	int		diff;

	start = philo->args->start_time;
	now = ft_time_get_usec();
	diff = ft_time_diff_msec(start, now);
	if (status == DONE)
		printf("DONE!\n");
	else if (status == FORK)
		printf("%d %d has taken a fork\n", diff, philo->id);
	else if (status == EAT)
		printf("%d %d is eating\n", diff, philo->id);
	else if (status == SLEEP)
		printf("%d %d is sleeping\n", diff, philo->id);
	else if (status == THINK)
		printf("%d %d is thinking\n", diff, philo->id);
	else if (status == DIED)
		printf("%d %d is died\n", diff, philo->id);
}
