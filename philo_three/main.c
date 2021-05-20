/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:12:38 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/21 02:34:00 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	_exec_child(t_philo *philo, pid_t *pids)
{
	free(pids);
	if (process_dining_philo(philo))
		exit(1);
	exit(0);
}

static int	_start_processes(t_global *global, pid_t *pids)
{
	int			i;
	pid_t		pid;

	global->start_time = ph_get_time_msec();
	i = 0;
	while (i < global->args.number_of_philo)
	{
		pid = fork();
		if (pid == -1)
		{
			free(pids);
			exit(process_kill(pids, i));
		}
		else if (pid == 0)
			_exec_child(&(global->philos[i]), pids);
		else
		{
			pids[i] = pid;
			i++;
		}
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_global	global;
	pid_t		*pids;

	memset(&global, 0, sizeof(t_global));
	if (ph_init_args(&(global.args), argc, argv))
		return (1);
	pids = malloc(sizeof(pid_t) * global.args.number_of_philo);
	if (pids == NULL)
		return (1);
	if (ph_init_global(&global))
		return (ph_sem_unlink_free(&global, global.args, pids)
			|| ph_put_err("error: fatal1\n"));
	if (_start_processes(&global, pids))
	{
		process_kill(pids, global.args.number_of_philo);
		ph_sem_unlink_free(&global, global.args, pids);
		return (ph_put_err("error: fatal2\n"));
	}
	process_wait(&global, pids);
	if (ph_sem_unlink_free(&global, global.args, pids))
		return (ph_put_err("error: fatal3\n"));
	return (0);
}
