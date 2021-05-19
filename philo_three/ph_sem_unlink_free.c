/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sem_unlink_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:52:45 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/19 15:54:06 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	_sem_unlink_philos(t_global *global, t_arg args)
{
	int		ret;
	int		i;
	char	dst[SEMNAMESIZE];

	ret = 0;
	i = 0;
	while (i < args.number_of_philo)
	{
		if (global->philos[i].sem != SEM_FAILED)
		{
			if (sem_close(global->philos[i].sem) != 0)
				ret++;
			ph_sem_create_name(dst, SEM, i);
			if (sem_unlink(dst) != 0)
				ret++;
		}
		i++;
	}
	return (ret);
}

static int	_sem_unlink_global1(t_global *global)
{
	int	ret;

	ret = 0;
	if (global->sem_forks != SEM_FAILED)
	{
		if (sem_close(global->sem_forks) != 0)
			ret++;
		if (sem_unlink(SEMFORKS) != 0)
			ret++;
	}
	if (global->sem_eat_cnt != SEM_FAILED)
	{
		if (sem_close(global->sem_eat_cnt) != 0)
			ret++;
		if (sem_unlink(SEMEATCNT) != 0)
			ret++;
	}
	if (global->sem_message != SEM_FAILED)
	{
		if (sem_close(global->sem_message) != 0)
			ret++;
		if (sem_unlink(SEMMESSAGE) != 0)
			ret++;
	}
	return (ret);
}

static int	_sem_unlink_global2(t_global *global)
{
	int	ret;

	ret = 0;
	if (global->sem_done != SEM_FAILED)
	{
		if (sem_close(global->sem_done) != 0)
			ret++;
		if (sem_unlink(SEMDONE) != 0)
			ret++;
	}
	if (global->sem_the_end != SEM_FAILED)
	{
		if (sem_close(global->sem_the_end) != 0)
			ret++;
		if (sem_unlink(SEMTHEEND) != 0)
			ret++;
	}
	return (ret);
}

int	ph_sem_unlink_free(t_global *global, t_arg args)
{
	int		ret;

	ret = 0;
	ret += _sem_unlink_global1(global);
	ret += _sem_unlink_global2(global);
	ret += _sem_unlink_philos(global, args);
	if (global->philos)
		free(global->philos);
	return (ret);
}
