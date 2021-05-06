/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:21:57 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/06 18:45:57 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int argc, char *argv[])
{
	t_arg			args;
	pthread_mutex_t	*forks;
	t_philo			**philos;
	t_monitor		monitor;

	if (ft_set_args(&args, argc, argv))
		return (1);
	ft_putargs(args);
	if (ft_set_forks(&forks, args.number_of_philo))
		return (1);
	if (ft_set_philos(&philos, &args, forks))
		return (1);
	if (ft_set_monitor(&monitor, philos, &args))
		return (1);
	if (ft_run_philos(&philos, &monitor, args))
		return (1);
	free(forks);
	ft_free_philos(&philos, args.number_of_philo);
	return (0);
}
