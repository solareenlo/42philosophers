/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 23:40:58 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/17 23:39:38 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ph_destroy_free(t_global *global, t_arg args)
{
	int	i;
	int	ret;

	ret = 0;
	/* pthread_mutex_unlock(&global->m_message); */
	if (pthread_mutex_destroy(&global->m_message) != 0)
	{
		printf("m_mesage\n");
		ret++;
	}
	if (pthread_mutex_destroy(&global->m_someone_is_dead) != 0)
	{
		printf("m_someone_is_dead\n");
		ret++;
	}
	pthread_mutex_unlock(&global->m_everyone_is_full);
	if (pthread_mutex_destroy(&global->m_everyone_is_full) != 0)
	{
		printf("m_everyone_is_full\n");
		ret++;
	}
	if (pthread_mutex_destroy(&global->m_done) != 0)
	{
		printf("m_done\n");
		ret++;
	}
	i = 0;
	while (i < args.number_of_philo)
	{
		pthread_mutex_unlock(&global->m_forks[i]);
		if (pthread_mutex_destroy(&global->m_forks[i]) != 0)
			ret++;
		pthread_mutex_unlock(&global->philos[i].m_time_limit);
		if (pthread_mutex_destroy(&global->philos[i].m_time_limit) != 0)
			ret++;
		pthread_mutex_unlock(&global->philos[i].m_eat_cnt);
		if (pthread_mutex_destroy(&global->philos[i].m_eat_cnt) != 0)
			ret++;
		i++;
	}
	free(global->philos);
	free(global->m_forks);
	printf("ret:%d\n", ret);
	return (ret);
}

int	ph_put_err(const char *err)
{
	if (err)
		write(2, err, ft_strlen(err));
	return (1);
}

void	_put_message(int type)
{
	if (type == DIED)
		printf("%s died\n%s", RED, RESET);
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
}

void	ph_put_message(t_philo *philo, int type)
{
	static int	done = 0;

	pthread_mutex_lock(&philo->global->m_message);
	if (done == 0)
	{
		printf("%ld\t", ph_get_time_msec() - philo->global->start_time);
		if (type != DONE)
			printf("%d", philo->pos + 1);
		_put_message(type);
		if (type == DONE || type == DIED)
			done = 1;
	}
	pthread_mutex_unlock(&philo->global->m_message);
}
