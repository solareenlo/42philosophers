/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:07:43 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/04 15:25:51 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

# define ARGERR "error: arg\nUsage: ./philo_one 1 2 3 4 [5]\n"
# define ARG1 "\t1: number_of_philosophers (1 ~ 2048)\n"
# define ARG2 "\t2: time_to_die (0 ~ 2147483647)\n"
# define ARG3 "\t3: time_to_eat (0 ~ 2147483647)\n"
# define ARG4 "\t4: time_to_sleep (0 ~ 2147483647)\n"
# define ARG5 "\t5: [number_of_times_each_philosopher_must_eat"
# define ARG6 " (0 ~ 2147483647)]\n"
# define LIMITTHREADS 2048
# define INTMAX 2147483647

typedef struct s_arg
{
	size_t	start_usec;
	size_t	number_of_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	number_ot_times_each_philo_must_eat;
}	t_arg;

typedef struct s_philo
{
	pthread_mutex_t	*mutex;
}	t_philo;

int		ft_atoi(const char *s);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_isspace(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_putargerr(void);
size_t	ft_get_time_usec(void);
int		ft_check_arg(int argc, char *argv[]);
int		ft_check_int(char *argv);

#endif
