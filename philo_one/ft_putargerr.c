/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putargerr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:51:17 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/04 04:20:08 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_putargerr(void)
{
	ft_putstr_fd(ARGERR, 2);
	ft_putstr_fd(ARG1, 2);
	ft_putstr_fd(ARG2, 2);
	ft_putstr_fd(ARG3, 2);
	ft_putstr_fd(ARG4, 2);
	ft_putstr_fd(ARG5, 2);
	return (1);
}
