/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 01:10:17 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/19 15:59:40 by tayamamo         ###   ########.fr       */
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
	else if (type == DONE)
	{
		ft_putstr_fd(BLUE, 1);
		ft_putstr_fd("Done!\n", 1);
		ft_putstr_fd(RESET, 1);
	}
}

int	ph_put_message(t_philo *philo, int type)
{
	static int	done = 0;

	if (philo->global->the_end == 1)
		return (0);
	if (sem_wait(philo->global->sem_message) != 0)
		return (1);
	if (done == 0)
	{
		ft_putnbr_fd(ph_get_time_msec() - philo->global->start_time, 1);
		ft_putstr_fd("\t", 1);
		if (type != DONE)
			ft_putnbr_fd(philo->pos + 1, 1);
		_put_message(type);
		if (type == DONE || type == DIED)
			done = 1;
	}
	if (sem_post(philo->global->sem_message) != 0)
		return (1);
	return (0);
}
