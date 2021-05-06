/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:45:10 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/06 18:46:56 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*_dining_philo(void *vars)
{
	t_philo	*philo;
	int		i;

	philo = vars;
	if (pthread_mutex_lock(philo->m_message) != 0)
		return (NULL);
	i = 0;
	while (42)
	{
		if (i > 3)
			break ;
		printf("id:%d\n", philo->id);
		i++;
	}
	if (pthread_mutex_unlock(philo->m_message) != 0)
		return (NULL);
	return (NULL);
}

int	ft_run_philos(t_philo ***philos, t_monitor *monitor, t_arg args)
{
	int	i;

	i = 0;
	while (i < args.number_of_philo)
	{
		(*philos)[i]->m_message = &(monitor->m_message);
		if (pthread_create(&((*philos)[i]->thread), NULL, &_dining_philo,
			(void *)(*philos)[i]) != 0)
			return (1);
		i++;
	}
	usleep(1000);
	i = 0;
	while (i < args.number_of_philo)
	{
		if (pthread_detach((*philos)[i]->thread) != 0)
			return (1);
		i++;
	}
	return (0);
}
