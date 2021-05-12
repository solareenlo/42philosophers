/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:24:57 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/13 04:44:45 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	*_monitor_count(void *arg)
{
	t_global	*global;
	int			i;
	int			total;

	global = (t_global *)arg;
	total = 0;
	while (total < global->args->number_of_times_each_philo_must_eat)
	{
		i = 0;
		while (i < global->args->number_of_philo)
			pthread_mutex_lock(&global->philos[i++].m_eat);
		total++;
	}
	ft_put_message(&global->philos[0], DONE);
	pthread_mutex_unlock(&global->m_done);
	return (NULL);
}

static int	_start_thread(t_global *global)
{
	int			i;
	pthread_t	thread;

	global->start_time = ft_get_time_msec();
	if (global->args->number_of_times_each_philo_must_eat > 0)
	{
		pthread_create(&thread, NULL, _monitor_count, (void *)global);
		pthread_detach(thread);
	}
	i = 0;
	while (i < global->args->number_of_philo)
	{
		pthread_create(&thread, NULL, ft_dining_philos,
			(void *)&(global->philos[i]));
		pthread_detach(thread);
		usleep(100);
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
	if (_start_thread(&global))
		return (ft_destroy_free(&global, args)
			&& ft_put_err("error: fatal\n"));
	pthread_mutex_lock(&global.m_done);
	pthread_mutex_lock(&global.m_message);
	pthread_mutex_unlock(&global.m_message);
	pthread_mutex_unlock(&global.m_done);
	ft_destroy_free(&global, args);
	return (0);
}
