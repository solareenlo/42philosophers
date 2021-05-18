/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:58:18 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/17 14:53:40 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	_puterr_arg(void)
{
	ft_putstr_fd("error: arg\nUsage: ./philo_one 1 2 3 4 [5]\n", 2);
	ft_putstr_fd("\t 1 : number_of_philosophers (2 ~ ", 2);
	ft_putnbr_fd(THREADSLIMIT, 2);
	ft_putstr_fd(")\n", 2);
	ft_putstr_fd("\t 2 : time_to_die (60 ~ ", 2);
	ft_putnbr_fd(TIMEMAX, 2);
	ft_putstr_fd(")\n", 2);
	ft_putstr_fd("\t 3 : time_to_eat (60 ~ ", 2);
	ft_putnbr_fd(TIMEMAX, 2);
	ft_putstr_fd(")\n", 2);
	ft_putstr_fd("\t 4 : time_to_sleep (60 ~ ", 2);
	ft_putnbr_fd(TIMEMAX, 2);
	ft_putstr_fd(")\n", 2);
	ft_putstr_fd("\t[5]: number_of_times_each_philosopher_must_eat", 2);
	ft_putstr_fd(" (0 ~ ", 2);
	ft_putnbr_fd(TIMEMAX, 2);
	ft_putstr_fd(")\n", 2);
	return (1);
}

static int	_puterr_arg_1(void)
{
	ft_putstr_fd("Error: arg1\n", 2);
	ft_putstr_fd("number_of_philosophers must be between 2 and ", 2);
	ft_putnbr_fd(THREADSLIMIT, 2);
	ft_putstr_fd(".\n", 2);
	return (1);
}

int	ph_check_arg(int argc, char *argv[])
{
	int	i;
	int	tmp;

	if (argc < 5 || 6 < argc)
		return (_puterr_arg());
	tmp = ft_atoi(argv[1]);
	if (ph_check_int(argv[1]) || tmp < 2 || THREADSLIMIT < tmp)
		return (_puterr_arg_1());
	i = 2;
	while (i < argc)
	{
		tmp = ft_atoi(argv[i]);
		if (i != 5)
		{
			if (ph_check_int(argv[i]) || tmp < TIMEMIN)
				return (_puterr_arg());
		}
		else
		{
			if (ph_check_int(argv[i]) || tmp < 0 || tmp > TIMEMAX)
				return (_puterr_arg());
		}
		i++;
	}
	return (0);
}
