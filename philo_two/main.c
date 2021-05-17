/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:24:10 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/18 02:25:38 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo_two.h"

int	main(int argc, char *argv[])
{
	t_arg		args;
	t_global	global;

	if (ph_init_args(&args, argc, argv))
		return (1);
	if (ph_init_global(&global, &args))
		return (ph_put_err("error: fatal1\n"));
	if (ph_unlink_free(&global, args))
		return (ph_put_err("error: fatal2\n"));
	return (0);
}
