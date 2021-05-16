/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:24:57 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/16 12:17:46 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	_start_threads(t_global *global)
{
	int			i;
	pthread_t	thread;

	global->start_time = ft_get_time_msec();
	if (global->args->number_of_times_each_philo_must_eat > 0)
	{
		pthread_create(&thread, NULL, thread_monitor_eat_cnt, (void *)global);
		pthread_detach(thread);
	}
	i = 0;
	while (i < global->args->number_of_philo)
	{
		pthread_create(&thread, NULL, thread_dining_philos,
			(void *)&(global->philos[i]));
		pthread_detach(thread);
		usleep(NEXTTHREAD);
		i++;
	}
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
	usleep(1000 * 1000);
	pthread_mutex_unlock(&global.m_message);
	pthread_mutex_unlock(&global.m_done);
	ft_destroy_free(&global, args);
	return (0);
}
