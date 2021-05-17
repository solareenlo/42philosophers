/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 05:15:59 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/17 21:55:36 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	ph_init_args(t_arg *args, int argc, char *argv[])
{
	if (ph_check_arg(argc, argv))
		return (1);
	args->number_of_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]) * 1000;
	args->time_to_eat = ft_atoi(argv[3]) * 1000;
	args->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
	{
		args->number_of_times_each_philo_must_eat = ft_atoi(argv[5]);
		if (args->number_of_times_each_philo_must_eat == 0)
			return (1);
	}
	else
		args->number_of_times_each_philo_must_eat = 0;
	return (0);
}

static int	_init_philos(t_global *global, t_arg *args)
{
	int		i;
	char	dst[SEMNAMESIZE];

	i = 0;
	while (i < args->number_of_philo)
	{
		global->philos[i].pos = i;
		global->philos[i].right_fork = i % args->number_of_philo;
		global->philos[i].left_fork = (i + 1) % args->number_of_philo;
		global->philos[i].eat_cnt = 0;
		global->philos[i].global = global;
		ph_create_sem_name(dst, SEMLIMIT, i);
		global->philos[i].sem_time_limit = ph_sem_open(dst, 1);
		if (global->philos[i].sem_time_limit == SEM_FAILED)
			return (1);
		ph_create_sem_name(dst, SEMCNT, i);
		global->philos[i].sem_eat_cnt = ph_sem_open(dst, 0);
		if (global->philos[i].sem_eat_cnt == SEM_FAILED)
			return (1);
		i++;
	}
	return (0);
}

int	ph_init_global(t_global *global, t_arg *args)
{
	int	ret;

	ret = 0;
	global->args = args;
	global->philos = malloc(sizeof(t_philo) * args->number_of_philo);
	if (global->philos == NULL)
		return (1);
	global->someone_is_dead = 0;
	global->sem_forks = ph_sem_open(SEMFORKS, args->number_of_philo);
	global->sem_message = ph_sem_open(SEMMESSAGE, 1);
	global->sem_someone_is_dead = ph_sem_open(SEMSOMEONE, 0);
	global->sem_done = ph_sem_open(SEMDONE, 0);
	ret = _init_philos(global, args);
	return (ret);
}