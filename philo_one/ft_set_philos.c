/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 18:05:36 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/06 16:28:19 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_set_philos(t_philo ***philos, t_arg *args, pthread_mutex_t *forks)
{
	int	i;

	*philos = ft_calloc(args->number_of_philo + 1, sizeof(t_philo *));
	if (*philos == NULL)
		return (ft_puterr_malloc());
	i = 0;
	while (i < args->number_of_philo)
	{
		(*philos)[i] = ft_calloc(1, sizeof(t_philo));
		if ((*philos)[i] == NULL)
		{
			ft_free_philos(philos, i + 1);
			return (ft_puterr_malloc());
		}
		(*philos)[i]->id = i + 1;
		(*philos)[i]->args = args;
		(*philos)[i]->last_time = args->start_time;
		(*philos)[i]->right_fork = &forks[i % args->number_of_philo];
		(*philos)[i]->left_fork = &forks[(i + 1) % args->number_of_philo];
		i++;
	}
	return (0);
}
