/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:35:15 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/19 21:34:23 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	ph_kill_processes(pid_t *pids, int cnt)
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

void	ph_wait_processes(pid_t *pids, t_arg args)
{
	pid_t	pid;
	int		i;
	int		stat_loc;

	pid = waitpid(-1, &stat_loc, 0);
	if (pid > 0)
	{
		if (WIFEXITED(stat_loc) && WEXITSTATUS(stat_loc))
		{
			i = 0;
			while (i < args.number_of_philo)
			{
				if (pid != pids[i])
					kill(pids[i], SIGKILL);
				i++;
			}
			exit(1);
		}
		else
			while (waitpid(-1, NULL, 0) > 0)
				;
	}
}

void	ph_wait_philosophers2(t_global *global, pid_t *pids)
{
	int	state;
	int	i;

	i = 0;
	while (i < global->args->number_of_philo)
	{
		waitpid(-1, &state, 0);
		if (WEXITSTATUS(state) == 1)
		{
			if (++i == global->args->number_of_philo)
				break ;
		}
		else
		{
			while (global->args->number_of_philo--)
			{
				kill(pids[global->args->number_of_philo], SIGKILL);
				usleep(500);
			}
			break ;
		}
	}
}
