/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:12:38 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/19 14:59:44 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	*_thread_monitor_eat_cnt(void *arg)
{
	int			i;
	t_global	*global;

	global = (t_global *)arg;
	i = global->args->number_of_philo;
	while (i--)
		sem_wait(global->sem_eat_cnt);
	ph_put_message(&global->philos[0], DONE);
	sem_post(global->sem_done);
	return (NULL);
}

static int	_start_processes(t_global *global)
{
	int			i;
	pthread_t	thread;

	global->start_time = ph_get_time_msec();
	if (global->args->number_of_times_each_philo_must_eat)
	{
		if (pthread_create(&thread, NULL, _thread_monitor_eat_cnt,
				(void *)global) != 0)
			return (1);
		if (pthread_detach(thread) != 0)
			return (1);
	}
	i = 0;
	while (i < global->args->number_of_philo)
	{
		global->philos[i].pid = fork();
		if (global->philos[i].pid == -1)
			exit(ph_kill_processes(global, i));
		else if (global->philos[i].pid == 0)
		{
			process_dining_philo(&(global->philos[i]));
			exit(0);
		}
		usleep(NEXTTHREAD);
		i += 2;
	}
	i = 1;
	while (i < global->args->number_of_philo)
	{
		global->philos[i].pid = fork();
		if (global->philos[i].pid == -1)
			exit(ph_kill_processes(global, i));
		else if (global->philos[i].pid == 0)
		{
			process_dining_philo(&(global->philos[i]));
			exit(0);
		}
		usleep(NEXTTHREAD);
		i += 2;
	}
	sem_wait(global->sem_done);
	/* sem_post(global->sem_the_end); */
	global->the_end = 1;
	/* sem_wait(global->sem_the_end); */
	i = global->args->number_of_philo;
	while (i--)
		sem_post(global->sem_eat_cnt);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_arg		args;
	t_global	global;

	memset(&args, 0, sizeof(t_arg));
	if (ph_init_args(&args, argc, argv))
		return (1);
	memset(&global, 0, sizeof(t_global));
	if (ph_init_global(&global, &args))
		return (ph_sem_unlink_free(&global, args)
			|| ph_put_err("error: fatal1\n"));
	_start_processes(&global);
	ph_kill_processes(&global, args.number_of_philo);
	usleep(1000);
	if (ph_sem_unlink_free(&global, args))
		return (ph_put_err("error: fatal3\n"));
	return (0);
}
