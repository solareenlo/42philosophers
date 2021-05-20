/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcess_kill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:10:55 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/20 15:11:42 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	process_kill(pid_t	*pids, int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	return (1);
}
