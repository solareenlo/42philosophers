/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:58:18 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/04 15:24:09 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	_puterr_arg(void)
{
	ft_putstr_fd(ARGERR, 2);
	ft_putstr_fd(ARG1, 2);
	ft_putstr_fd(ARG2, 2);
	ft_putstr_fd(ARG3, 2);
	ft_putstr_fd(ARG4, 2);
	ft_putstr_fd(ARG5, 2);
	ft_putstr_fd(ARG6, 2);
	return (1);
}

static int	_puterr_arg_1(void)
{
	ft_putstr_fd("Error: arg1\n", 2);
	ft_putstr_fd("number_of_philosophers must be between 2 and 2048.\n", 2);
	return (1);
}

static int	_puterr_arg_n(int i)
{
	ft_putstr_fd("Error: arg", 2);
	ft_putnbr_fd(i, 2);
	ft_putstr_fd("\n", 2);
	if (i == 2)
		ft_putstr_fd("time_to_die", 2);
	else if (i == 3)
		ft_putstr_fd("time_to_eat", 2);
	else if (i == 4)
		ft_putstr_fd("time_to_sleep", 2);
	else if (i == 5)
		ft_putstr_fd("number_of_times_each_philosopher_must_eat", 2);
	ft_putstr_fd(" must be between 0 and 2147483647.\n", 2);
	return (1);
}

int	ft_check_arg(int argc, char *argv[])
{
	int	i;
	int	tmp;

	if (argc < 5 || 6 < argc)
		return (_puterr_arg());
	tmp = ft_atoi(argv[1]);
	if (ft_check_int(argv[1]) || tmp < 2 || 2048 < tmp)
		return (_puterr_arg_1());
	i = 2;
	while (i < argc)
	{
		tmp = ft_atoi(argv[i]);
		if (ft_check_int(argv[i]) || tmp < 0)
			return (_puterr_arg_n(i));
		i++;
	}
	return (0);
}
