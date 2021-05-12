/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 03:50:49 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/12 12:30:57 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	*_monitor_cnt(void *arg)
{
	t_global	*global;
	t_arg		*args;
	int			i;
	int			sum;

	global = (t_global *)arg;
	args = global->args;
	sum = 0;
	while (sum < args->number_of_times_each_philo_must_eat)
	{
		i = 0;
		while (i < args->number_of_philo)
		{
			pthread_mutex_lock(&(global->philos[i].m_eat));
			i++;
		}
		sum++;
	}
	return (NULL);
}

static	int	_run_threads(t_global *global)
{
	pthread_t	thread;
	int			i;
	t_philo		*philo;

	global->start_time = ft_get_time_msec();
	if (global->args->number_of_times_each_philo_must_eat > 0)
	{
		if (pthread_create(&thread, NULL, &_monitor_cnt, (void *)global) != 0)
			return (1);
		pthread_detach(thread);
	}
	i = 0;
	while (i < global->args->number_of_philo)
	{
		philo = &global->philos[i];
		if (pthread_create(&thread, NULL, &ft_dining_philo, (void *)philo) != 0)
			return (1);
		pthread_detach(thread);
		ft_usleep(100);
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
	global.m_forks = NULL;
	if (ft_init_philos(&args, &global))
		return (ft_destory_free(args, &global)
				&& ft_put_err("error: fatal\n"));
	if (ft_init_global(&args, &global))
		return (ft_destory_free(args, &global)
				&& ft_put_err("error: fatal\n"));
	if (_run_threads(&global))
		return (ft_destory_free(args, &global)
				&& ft_put_err("error: fatal\n"));
	pthread_mutex_lock(&global.m_died);
	pthread_mutex_unlock(&global.m_died);
	ft_destory_free(args, &global);
	return (0);
}
