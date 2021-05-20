/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 05:15:59 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/21 02:22:36 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

static int	_sem_create_name(t_global *global)
{
	int		i;
	int		ret;
	char	dst[SEMNAMESIZE];

	ret = 0;
	i = 0;
	while (i < global->args.number_of_philo)
	{
		ph_sem_create_name(dst, SEM, i);
		global->philos[i].sem = ph_sem_open(dst, 1);
		if (global->philos[i].sem == SEM_FAILED)
			ret++;
		i++;
	}
	return (ret);
}

static int	_init_philos(t_global *global)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < global->args.number_of_philo)
	{
		global->philos[i].alive = TRUE;
		global->philos[i].type = FORK;
		global->philos[i].pos = i;
		global->philos[i].eat_cnt = 0;
		global->philos[i].global = global;
		i++;
	}
	ret += _sem_create_name(global);
	return (ret);
}

int	ph_init_global(t_global *global)
{
	int		ret;

	ret = 0;
	global->philos = malloc(sizeof(t_philo) * global->args.number_of_philo);
	if (global->philos == NULL)
		return (1);
	global->sem_forks = ph_sem_open(SEMFORKS, global->args.number_of_philo);
	if (global->sem_forks == SEM_FAILED)
		ret++;
	global->sem_message = ph_sem_open(SEMMESSAGE, 1);
	if (global->sem_message == SEM_FAILED)
		ret++;
	ret += _init_philos(global);
	return (ret);
}
