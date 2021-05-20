/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:12:38 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/19 22:21:17 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	_run_processes(t_global *global, int start, pid_t *pids)
{
	int			i;
	pid_t		pid;

	global->start_time = ph_get_time_msec();
	i = start;
	while (i < global->args->number_of_philo)
	{
		pid = fork();
		if (pid == -1)
			exit(ph_kill_processes(pids, i));
		else if (pid == 0)
		{
			process_dining_philo(&(global->philos[i]));
			exit(0);
		}
		pids[i] = pid;
		i += 2;
		usleep(NEXTPROCESS);
	}
}

static int	_start_processes(t_global *global, pid_t *pids)
{
	int	i;

	global->start_time = ph_get_time_msec();
	_run_processes(global, 0, pids);
	_run_processes(global, 1, pids);
	sem_wait(global->sem_done);
	/* global->the_end = 1; */
	i = global->args->number_of_philo;
	while (i--)
		sem_post(global->sem_eat_cnt);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_arg		args;
	t_global	global;
	pid_t		*pids;

	memset(&args, 0, sizeof(t_arg));
	if (ph_init_args(&args, argc, argv))
		return (1);
	pids = malloc(sizeof(pid_t) * args.number_of_philo);
	if (pids == NULL)
		return (1);
	memset(&global, 0, sizeof(t_global));
	if (ph_init_global(&global, &args))
		return (ph_sem_unlink_free(&global, args, pids)
			|| ph_put_err("error: fatal1\n"));
	if (global.args->number_of_times_each_philo_must_eat)
		if (thread_monitor_eat_cnt(&global))
			return (ph_sem_unlink_free(&global, args, pids)
				|| ph_put_err("error: fatal2\n"));
	_start_processes(&global, pids);
	ph_wait_philosophers2(&global, pids);
	/* ph_kill_processes(pids, args.number_of_philo); */
	usleep(1000);
	if (ph_sem_unlink_free(&global, args, pids))
		return (ph_put_err("error: fatal3\n"));
	return (0);
}
