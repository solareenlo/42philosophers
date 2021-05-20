/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:06:37 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/21 02:18:48 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	process_wait(t_global *global, pid_t *pids)
{
	int	status;
	int	i;

	waitpid(-1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		process_kill(pids, global->args.number_of_philo);
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		i = 0;
		while (i < global->args.number_of_philo)
		{
			waitpid(-1, &status, 0);
			if (++i == global->args.number_of_philo)
				break ;
		}
	}
}
