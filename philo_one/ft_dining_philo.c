/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dining_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:52:31 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/06 18:54:23 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ft_dining_philo(void *var)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)var;
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
