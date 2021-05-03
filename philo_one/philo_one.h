/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:07:43 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/04 04:05:04 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define ARGERR "error: arg\nUsage: ./philo_one 1 2 3 4 [5]\n"
# define ARG1 "\t1: number_of_philosophers\n"
# define ARG2 "\t2: time_to_die\n"
# define ARG3 "\t3: time_to_eat\n"
# define ARG4 "\t4: time_to_sleep\n"
# define ARG5 "\t5: [number_of_times_each_philosopher_must_eat]\n"

int		ft_atoi(const char *s);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_isspace(int c);
void	ft_puterr(char *err);
int		ft_putargerr(void);

#endif
