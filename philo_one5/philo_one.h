/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:07:43 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/11 14:22:16 by tayamamo         ###   ########.fr       */
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

# define THREADSLIMIT	1000
# define INTMAX			2147483647
# define FORK			0x001
# define EAT			0x002
# define SLEEP			0x004
# define THINK			0x008
# define DIED			0x010
# define DONE			0x020

typedef struct s_arg
{
	size_t	start_time;
	int		number_of_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	number_of_times_each_philo_must_eat;
}	t_arg;

typedef struct s_philo
{
	pthread_t		thread;
	t_arg			*args;
	size_t			last_time;
	int				pos;
	int				cnt;
	int				done;
	int				right_fork;
	int				left_fork;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_monitor
{
	pthread_t		thread;
	t_arg			*args;
	t_philo			*philos;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_message;
	pthread_mutex_t	m_died;
}	t_monitor;

int		ft_check_arg(int argc, char *argv[]);
int		ft_check_int(char *argv);
int		ft_set_args(t_arg *args, int argc, char *argv[]);
void	ft_put_args(t_arg args);
int		ft_put_err(const char *err);
int		ft_destory_free(t_arg args, t_philo **philos, t_monitor *monitor);

size_t	ft_time_get_usec(void);
size_t	ft_time_get_msec(void);
size_t	ft_time_diff_msec(size_t start, size_t end);
size_t	ft_time_diff_usec(size_t start, size_t end);
void	ft_time_usleep(size_t sleep);

int		ft_atoi(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t cnt, size_t size);
int		ft_isdigit(int c);
int		ft_isspace(int c);
void	*ft_memset(void *dst, int val, size_t n);
void	ft_putchar_fd(char c, int fd);
int		ft_puterr_malloc(void);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);

#endif
