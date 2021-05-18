/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 02:43:10 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/18 12:53:51 by tayamamo         ###   ########.fr       */
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
	errno = 0;
	sem = sem_open(name, oflag, mode, value);
	if (sem == SEM_FAILED)
	{
		printf("EACCES:%d, EEXIST:%d, EINTR:%d, EINVAL:%d, ENAMETOOLONG:%d, ENFILE:%d, ENOENT:%d, ENOSPC:%d\n",
				EACCES,
				EEXIST,
				EINTR,
				EINVAL,
				ENAMETOOLONG,
				ENFILE,
				ENOENT,
				ENOSPC);
		printf("error%d: sem_open: %s\n", errno, name);
	}
	errno = 0;
	if (sem_unlink(name) != 0)
	{
		printf("EACCES:%d, ENAMETOOLONG:%d, ENOENT:%d\n", EACCES, ENAMETOOLONG, ENOENT);
		printf("error%d: unlink: %s\n", errno, name);
	}
	/* if (sem == SEM_FAILED) */
	/* { */
	/* 	sem_unlink(name); */
	/* 	sem = sem_open(name, oflag, mode, value); */
	/* } */
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

/* static int	_sem_unlinks(t_arg args) */
/* { */
/* 	int		ret; */
/* 	int		i; */
/* 	char	dst[SEMNAMESIZE]; */
/*  */
/* 	ret = 0; */
/* 	i = 0; */
/* 	while (i < args.number_of_philo) */
/* 	{ */
/* 		ph_sem_create_name(dst, SEMLIMIT, i); */
/* 		if (sem_unlink(dst) != 0) */
/* 			ret++; */
/* 		if (args.number_of_times_each_philo_must_eat) */
/* 		{ */
/* 			ph_sem_create_name(dst, SEMCNT, i); */
/* 			if (sem_unlink(dst) != 0) */
/* 				ret++; */
/* 		} */
/* 		i++; */
/* 	} */
/* 	return (ret); */
/* } */

int	ph_unlink_free(t_global *global, t_arg args)
{
	int		ret;

	ret = 0;
	(void)args;
	/* if (sem_unlink(SEMFORKS) != 0) */
	/* 	ret++; */
	/* if (sem_unlink(SEMMESSAGE) != 0) */
	/* 	ret++; */
	/* if (sem_unlink(SEMDONE) != 0) */
	/* 	ret++; */
	/* ret += _sem_unlinks(args); */
	free(global->philos);
	return (ret);
}
