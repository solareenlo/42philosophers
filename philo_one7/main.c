/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:24:57 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/12 23:16:30 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*_start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_eat = ft_get_time_usec();
	return (NULL);
}

int	ft_start_thread_philo(t_global *global)
{
	int	i;

	global->start_time = ft_get_time_usec();
	i = 0;
	while (i < global->args->number_of_philo)
	{
		global->philos[i].last_eat = ft_get_time_usec();
		pthread_create(&global->philos[i].thread, NULL, _start_routine, &global->philos[i]);
		i++;
	}
	return (0);
}

int	ft_start_thread(t_global *global)
{
	if (ft_start_thread_philo(global))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_arg		args;
	t_global	global;

	if (ft_init_args(&args, argc, argv))
		return (1);
	if (ft_init_philos(&global, args))
		return (ft_free_destroy(&global, args)
			&& ft_put_err("error: fatal\n"));
	return (0);
}
