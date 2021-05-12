/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:19:23 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/12 20:10:15 by tayamamo         ###   ########.fr       */
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

void	_put_message(int type)
{
	if (type == FORK)
		printf(" has taken a fork\n");
	else if (type == EAT)
		printf("%s is eating\n%s", GREEN, RESET);
	else if (type == SLEEP)
		printf (" is sleeping\n");
	else if (type == THINK)
		printf(" is thinkig\n");
	else if (type == DONE)
		printf("%sDone!\n%s", BLUE, RESET);
	else
		printf("%s died\n%s", RED, RESET);
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
		_put_message(type);
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
