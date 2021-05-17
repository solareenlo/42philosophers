/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 23:40:58 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/18 01:40:47 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ph_put_err(const char *err)
{
	if (err)
		write(2, err, ft_strlen(err));
	return (1);
}

void	_put_message(int type)
{
	if (type == DIED)
		printf("%s died\n%s", RED, RESET);
	if (type == FORK)
		printf(" has taken a fork\n");
	else if (type == EAT)
		printf("%s is eating\n%s", GREEN, RESET);
	else if (type == SLEEP)
		printf (" is sleeping\n");
	else if (type == THINK)
		printf(" is thinkig\n");
	else if (type == DONE)
		printf("%sDone!\n%s", BLUE, RESET);
}

int	ph_put_message(t_philo *philo, int type)
{
	static int	done = 0;

	if (pthread_mutex_lock(&philo->global->m_message) != 0)
		return (1);
	if (done == 0)
	{
		printf("%ld\t", ph_get_time_msec() - philo->global->start_time);
		if (type != DONE)
			printf("%d", philo->pos + 1);
		_put_message(type);
		if (type == DONE || type == DIED)
			done = 1;
	}
	if (pthread_mutex_unlock(&philo->global->m_message) != 0)
		return (1);
	return (0);
}
