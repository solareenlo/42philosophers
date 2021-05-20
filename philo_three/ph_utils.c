/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 01:10:17 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/21 02:01:22 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	ph_put_err(const char *err)
{
	if (err)
		write(2, err, ft_strlen(err));
	return (1);
}

void	_put_message(int type)
{
	if (type == DIED)
	{
		ft_putstr_fd(RED, 1);
		ft_putstr_fd(" died\n", 1);
		ft_putstr_fd(RESET, 1);
	}
	if (type == FORK)
		ft_putstr_fd(" has taken a fork\n", 1);
	else if (type == EAT)
	{
		ft_putstr_fd(GREEN, 1);
		ft_putstr_fd(" is eating\n", 1);
		ft_putstr_fd(RESET, 1);
	}
	else if (type == SLEEP)
		ft_putstr_fd(" is sleeping\n", 1);
	else if (type == THINK)
		ft_putstr_fd(" is thinkig\n", 1);
}

int	ph_put_message(t_philo *philo, int type)
{
	if (sem_wait(philo->global->sem_message) != 0)
		return (1);
	ft_putnbr_fd(ph_get_time_msec() - philo->global->start_time, 1);
	ft_putstr_fd("\t", 1);
	ft_putnbr_fd(philo->pos + 1, 1);
	_put_message(type);
	if (sem_post(philo->global->sem_message) != 0)
		return (1);
	return (0);
}
