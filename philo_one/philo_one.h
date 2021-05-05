/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:07:43 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/06 03:01:30 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define LIMITTHREADS	2048
# define INTMAX			2147483647
# define FORK			0x001
# define EAT			0x002
# define SLEEP			0x004
# define THINK			0x008
# define DIED			0x010

typedef struct s_arg
{
	int	number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_ot_times_each_philo_must_eat;
}	t_arg;

typedef struct s_philo
{
	size_t			start_usec;
	pthread_t		*threads;
	pthread_mutex_t	*mutex;
}	t_philo;

int				ft_atoi(const char *s);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t cnt, size_t size);
int				ft_isdigit(int c);
int				ft_isspace(int c);
void			*ft_memset(void *dst, int val, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
size_t			ft_strlen(const char *s);
int				ft_putargerr(void);
size_t			ft_get_time_usec(void);
int				ft_check_arg(int argc, char *argv[]);
int				ft_check_int(char *argv);
pthread_mutex_t	*ft_init_mutex(int n);
int				ft_set_args(int argc, char *argv[], t_arg *args);
void			ft_putargs(t_arg args);
int				ft_set_philo(t_arg args, t_philo *philo);
void			ft_free_philo(t_philo *philo);

#endif
