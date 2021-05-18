/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 02:43:10 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/18 19:01:06 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

sem_t	*ph_sem_open(char *name, int value)
{
	int		oflag;
	mode_t	mode;
	sem_t	*sem;

	oflag = O_CREAT | O_EXCL;
	mode = S_IRWXU | S_IRGRP | S_IROTH;
	sem = sem_open(name, oflag, mode, value);
	if (sem == SEM_FAILED)
	{
		sem_unlink(name);
		sem = sem_open(name, oflag, mode, value);
	}
	return (sem);
}

char	*ph_sem_create_name(char *dst, char *name, int nbr)
{
	char	*num;

	ft_strlcpy(dst, name, SEMNAMESIZE);
	num = ft_itoa(nbr);
	if (num == NULL)
		return (NULL);
	ft_strlcat(dst, num, SEMNAMESIZE);
	free(num);
	return (dst);
}

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

static int	_sem_unlink_global(t_global *global)
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
	if (global->sem_message != SEM_FAILED)
	{
		if (sem_close(global->sem_message) != 0)
			ret++;
		if (sem_unlink(SEMMESSAGE) != 0)
			ret++;
	}
	if (global->sem_done != SEM_FAILED)
	{
		if (sem_close(global->sem_done) != 0)
			ret++;
		if (sem_unlink(SEMDONE) != 0)
			ret++;
	}
	return (ret);
}

int	ph_sem_unlink_free(t_global *global, t_arg args)
{
	int		ret;

	ret = 0;
	ret += _sem_unlink_global(global);
	ret += _sem_unlink_philos(global, args);
	if (global->philos)
		free(global->philos);
	return (ret);
}
