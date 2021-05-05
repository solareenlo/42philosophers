/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 18:05:36 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/06 03:04:05 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	_puterr_malloc(void)
{
	ft_putstr_fd("Error: malloc failed\n", 2);
	return (1);
}

int	ft_set_philo(t_arg args, t_philo *philo)
{
	philo->start_usec = ft_get_time_usec();
	philo->threads = ft_calloc(args.number_of_philo, sizeof(pthread_t));
	if (philo->threads == NULL)
		return (_puterr_malloc());
	philo->mutex = ft_init_mutex(args.number_of_philo);
	if (philo->mutex == NULL)
	{
		free(philo->threads);
		return (_puterr_malloc());
	}
	return (0);
}
