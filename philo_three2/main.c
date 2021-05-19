/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:12:38 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/19 18:32:04 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	_thread_monitor_eat_cnt(t_global *global)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, thread_monitor_eat_cnt,
			(void *)global) != 0)
		return (1);
	if (pthread_detach(thread) != 0)
		return (1);
	return (0);
}

static int	_start_processes(t_global *global, pid_t *pids)
{
	int			i;
	pid_t		pid;

	if (global->args->number_of_times_each_philo_must_eat)
		if (_thread_monitor_eat_cnt(global))
			return (1);
	global->start_time = ph_get_time_msec();
	i = 0;
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
		usleep(NEXTTHREAD);
		pids[i] = pid;
		i += 2;
	}
	i = 1;
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
		usleep(NEXTTHREAD);
		i += 2;
	}
	sem_wait(global->sem_done);
	global->the_end = 1;
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
	_start_processes(&global, pids);
	ph_kill_processes(pids, args.number_of_philo);
	usleep(1000);
	if (ph_sem_unlink_free(&global, args, pids))
		return (ph_put_err("error: fatal3\n"));
	return (0);
}
