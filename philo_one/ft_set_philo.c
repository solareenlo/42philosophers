/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 18:05:36 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/06 10:03:35 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	_puterr_malloc(void)
{
	ft_putstr_fd("Error: malloc failed\n", 2);
	return (1);
}

int	ft_set_philo(t_philo *philo, t_arg args)
{
	ft_memset(philo, 0, sizeof(*philo));
	philo->args = &args;
	return (0);
}
