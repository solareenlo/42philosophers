/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 02:43:10 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/19 15:59:03 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
