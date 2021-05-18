/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:24:10 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/18 09:39:20 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	_start_philos(t_global *global, int i)
{
	pthread_t	thread;

	while (i < global->args->number_of_philo)
	{
		if (pthread_create(&thread, NULL, thread_dining_philo,
				(void *)&(global->philos[i])) != 0)
			return (1);
		if (pthread_detach(thread) != 0)
			return (1);
		usleep(ft_max(NEXTTHREAD, global->philos[i].pos));
		i += 2;
	}
	return (0);
}

static int	_start_threads(t_global *global)
{
	pthread_t	thread;

	global->start_time = ph_get_time_msec();
	if (global->args->number_of_times_each_philo_must_eat)
	{
		if (pthread_create(&thread, NULL, thread_monitor_eat_cnt,
				(void *)global) != 0)
			return (1);
		if (pthread_detach(thread) != 0)
			return (1);
	}
	if (_start_philos(global, 0))
		return (1);
	if (_start_philos(global, 1))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_arg		args;
	t_global	global;

	if (ph_init_args(&args, argc, argv))
		return (1);
	if (ph_init_global(&global, &args))
		return (ph_put_err("error: fatal\n"));
	if (_start_threads(&global))
		return (ph_unlink_free(&global, args) && ph_put_err("error: fatal\n"));
	sem_wait(global.sem_done);
	global.done = 1;
	usleep(1000 * 1000);
	if (ph_unlink_free(&global, args))
		return (ph_put_err("error: fatal\n"));
	return (0);
}
