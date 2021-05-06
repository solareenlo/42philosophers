/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dining_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:52:31 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/07 05:31:13 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	*_fork(t_philo *philo)
{
	if (philo->id % 2)
	{
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (NULL);
	}
	else
	{
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (NULL);
	}
	if (ft_mutex_put_message(philo, FORK) == NULL)
		return (NULL);
	if (philo->id % 2)
	{
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (NULL);
	}
	else
	{
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (NULL);
	}
	if (ft_mutex_put_message(philo, FORK) == NULL)
		return (NULL);
	return (philo);
}

static void	*_cnt_eating(t_philo *philo)
{
	philo->cnt++;
	if (philo->cnt == philo->args->number_ot_times_each_philo_must_eat)
	{
		if (pthread_mutex_lock(philo->m_done) != 0)
			return (NULL);
		philo->done = 1;
		if (pthread_mutex_unlock(philo->m_done) != 0)
			return (NULL);
	}
	return (philo);
}

static void	*_eating(t_philo *philo)
{
	if (ft_mutex_put_message(philo, EAT) == NULL)
		return (NULL);
	if (philo->args->number_ot_times_each_philo_must_eat != -1)
		_cnt_eating(philo);
	if (pthread_mutex_unlock(philo->right_fork) != 0)
		return (NULL);
	if (pthread_mutex_unlock(philo->left_fork) != 0)
		return (NULL);
	return (philo);
}

void	*ft_dining_philo(void *var)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)var;
	i = 0;
	while (42)
	{
		if (i > 0)
			break ;
		if (_fork(philo) == NULL)
			return (var);
		if (_eating(philo) == NULL)
			return (var);
		if (ft_mutex_put_message(philo, SLEEP) == NULL)
			return (var);
		if (ft_mutex_put_message(philo, THINK) == NULL)
			return (var);
		i++;
	}
	return (NULL);
}
