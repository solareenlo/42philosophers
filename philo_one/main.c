/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:24:57 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/16 15:42:41 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	_start_philos(t_global *global, int i)
{
	pthread_t	thread;

	while (i < global->args->number_of_philo)
	{
		pthread_create(&thread, NULL, thread_dining_philo,
			(void *)&(global->philos[i]));
		pthread_detach(thread);
		usleep(ft_max(50, global->philos[i].pos));
		i += 2;
	}
}

static int	_start_threads(t_global *global)
{
	pthread_t	thread;

	global->start_time = ft_get_time_msec();
	if (global->args->number_of_times_each_philo_must_eat > 0)
	{
		pthread_create(&thread, NULL, thread_monitor_eat_cnt, (void *)global);
		pthread_detach(thread);
	}
	_start_philos(global, 0);
	_start_philos(global, 1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_arg		args;
	t_global	global;

	if (ft_init_args(&args, argc, argv))
		return (1);
	if (ft_init_global(&global, &args))
		return (ft_put_err("error: fatal\n"));
	if (_start_threads(&global))
		return (ft_destroy_free(&global, args)
			&& ft_put_err("error: fatal\n"));
	pthread_mutex_lock(&global.m_done);
	pthread_mutex_lock(&global.m_message);
	pthread_mutex_unlock(&global.m_message);
	usleep(1000 * 1000);
	pthread_mutex_unlock(&global.m_done);
	ft_destroy_free(&global, args);
	return (0);
}
