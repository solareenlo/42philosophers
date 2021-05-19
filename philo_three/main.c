/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:12:38 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/19 13:53:27 by tayamamo         ###   ########.fr       */
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

static int	_start_processes(t_global *global, int start)
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
	i = start;
	while (i < global->args->number_of_philo)
	{
		global->philos[i].pid = fork();
		if (global->philos[i].pid == -1)
			exit(ph_kill_processes(global, i));
		else if (global->philos[i].pid == 0)
		{
			process_dining_philo(&(global->philos[i]));
			break ;
			exit(0);
		}
		usleep(NEXTTHREAD);
		i += 2;
	}
	usleep(NEXTTHREAD);
	i = start + 1;
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
	sem_wait(global->sem_the_end);
	sem_wait(global->sem_done);
	global->done = 1;
	sem_post(global->sem_the_end);
	i = global->args->number_of_philo;
	while (i--)
		sem_post(global->sem_eat_cnt);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_arg		args;
	t_global	global;

	setbuf(stdout, NULL);
	memset(&args, 0, sizeof(t_arg));
	if (ph_init_args(&args, argc, argv))
		return (1);
	memset(&global, 0, sizeof(t_global));
	if (ph_init_global(&global, &args))
		return (ph_sem_unlink_free(&global, args)
			|| ph_put_err("error: fatal1\n"));
	_start_processes(&global, 0);
	/* ph_wait_processes(&global, args); */
	/* int i = 0; */
	/* while (i < args.number_of_philo) */
	/* { */
	/* 	while (global.philos[i].pid == waitpid (-1, NULL, 0)) */
	/* 	{ */
	/* 		if (errno == ECHILD) */
	/* 			break; */
	/* 	} */
	/* 	i++; */
	/* } */
	ph_kill_processes(&global, args.number_of_philo);
	usleep(1000);
	if (ph_sem_unlink_free(&global, args))
		return (ph_put_err("error: fatal3\n"));
	return (0);
}
