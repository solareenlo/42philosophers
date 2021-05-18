/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 02:43:10 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/18 02:47:50 by tayamamo         ###   ########.fr       */
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

int	ph_unlink_free(t_global *global, t_arg args)
{
	int		i;
	int		ret;
	char	dst[SEMNAMESIZE];

	ret = 0;
	if (sem_unlink(SEMFORKS) != 0)
		ret++;
	if (sem_unlink(SEMMESSAGE) != 0)
		ret++;
	if (sem_unlink(SEMDONE) != 0)
		ret++;
	i = -1;
	while (++i < args.number_of_philo)
	{
		ph_sem_create_name(dst, SEMLIMIT, i);
		if (sem_unlink(dst) != 0)
			ret++;
		ph_sem_create_name(dst, SEMCNT, i);
		if (sem_unlink(dst) != 0)
			ret++;
	}
	free(global->philos);
	return (ret);
}
