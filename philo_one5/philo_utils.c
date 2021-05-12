/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:19:23 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/12 12:33:43 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_put_args(t_arg args)
{
	printf("%d\n", args.number_of_philo);
	printf("%zu\n", args.time_to_die);
	printf("%zu\n", args.time_to_eat);
	printf("%zu\n", args.time_to_sleep);
	if (args.number_of_times_each_philo_must_eat != 0)
		printf("%d\n", args.number_of_times_each_philo_must_eat);
}

int	ft_put_err(const char *err)
{
	if (err)
		write(2, err, ft_strlen(err));
	return (1);
}

char	*_get_message(int type)
{
	if (type == FORK)
		return (" has taken a fork");
	else if (type == EAT)
		return (" is eating");
	else if (type == SLEEP)
		return (" is sleeping");
	else if (type == THINK)
		return  (" is thinkig");
	else if (type == DONE)
		return ("Done!");
	else
		return (" died");
}

void	ft_put_message(t_philo *philo, int type)
{
	static int	done = 0;

	pthread_mutex_lock(&philo->global->m_message);
	if (done == 0)
	{
		printf("%ld\t", ft_get_time_msec() - philo->global->start_time);
		if (type != DONE)
			printf("%d", philo->pos + 1);
		else if (type == DONE)
			done = 1;
		printf("%s\n", _get_message(type));
	}
	pthread_mutex_unlock(&philo->global->m_message);
}

int	ft_destory_free(t_arg args, t_global *global)
{
	int	i;

	if (global->philos != NULL)
	{
		i = 0;
		while (i < args.number_of_philo)
		{
			pthread_mutex_destroy(&global->philos[i].mutex);
			pthread_mutex_destroy(&global->philos[i].m_eat);
			i++;
		}
		free(global->philos);
	}
	if (global->m_forks != NULL)
	{
		i = 0;
		while (i < args.number_of_philo)
			pthread_mutex_destroy(&global->m_forks[i++]);
		free(global->m_forks);
		pthread_mutex_destroy(&global->m_message);
		pthread_mutex_destroy(&global->m_died);
	}
	return (1);
}
