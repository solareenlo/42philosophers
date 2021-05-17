/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:24:57 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/18 02:04:46 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
	if (global->args->number_of_times_each_philo_must_eat > 0)
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
		return (ph_destroy_free(&global, args)
			&& ph_put_err("error: fatal\n"));
	if (pthread_mutex_lock(&global.m_done) != 0)
		return (ph_destroy_free(&global, args)
			&& ph_put_err("error: fatal\n"));
	global.done = 1;
	usleep(1000 * 1000);
	if (ph_destroy_free(&global, args))
		return (ph_put_err("error: fata;\n"));
	return (0);
}
