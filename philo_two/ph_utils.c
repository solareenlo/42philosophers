/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 01:10:17 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/17 21:55:28 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	ph_put_err(const char *err)
{
	if (err)
		write(2, err, ft_strlen(err));
	return (1);
}

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

char	*ph_create_sem_name(char *dst, char *name, int nbr)
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
	int		err_cnt;
	char	dst[SEMNAMESIZE];

	err_cnt = 0;
	if (sem_unlink(SEMFORKS) != 0)
		err_cnt++;
	if (sem_unlink(SEMMESSAGE) != 0)
		err_cnt++;
	if (sem_unlink(SEMSOMEONE) != 0)
		err_cnt++;
	if (sem_unlink(SEMDONE) != 0)
		err_cnt++;
	i = -1;
	while (++i < args.number_of_philo)
	{
		ph_create_sem_name(dst, SEMLIMIT, i);
		if (sem_unlink(dst) != 0)
			err_cnt++;
		ph_create_sem_name(dst, SEMCNT, i);
		if (sem_unlink(dst) != 0)
			err_cnt++;
	}
	free(global->philos);
	return (err_cnt);
}
