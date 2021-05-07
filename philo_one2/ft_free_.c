/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:55:31 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/06 17:42:50 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_free_philos(t_philo ***philos, int n)
{
	int	i;

	if (*philos == NULL)
		return ;
	i = 0;
	while (i < n)
	{
		free((*philos)[i]);
		i++;
	}
	free(*philos);
}
