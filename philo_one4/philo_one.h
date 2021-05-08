/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:07:43 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/08 12:09:10 by tayamamo         ###   ########.fr       */
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
# define DONE			0x020

typedef struct s_args
{
	size_t		start_time;
	int			limit_times_to_eat;
	unsigned	number_of_philo;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			number_of_times_each_philo_must_eat;
}	t_args;

typedef struct	s_philo
{
	t_args			*args;
	pthread_t		thread;
	unsigned		id;
	size_t			last_eat_time;
	unsigned		eat_count;
	unsigned		dining_complete;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	*print_status;
	pthread_mutex_t	*check_starvation;
	pthread_mutex_t *check_dining_complete;
}				t_philo;

typedef struct	s_monitor
{
	t_args			*args;
	t_philo			*ph;
	pthread_t		thread;
	pthread_mutex_t	*check_starvation;
	pthread_mutex_t	print_status;
	pthread_mutex_t	*check_dining_complete;
}				t_monitor;

int		ft_check_arg(int argc, char *argv[]);
int		ft_check_int(char *argv);
int		ft_set_args(t_args *args, int argc, char *argv[]);
void	ft_put_args(t_args args);
void	ft_put_status(t_philo *philo, int status);
void	ft_put_message(t_philo *philo, int status);
size_t	ft_time_get_usec(void);
size_t	ft_time_get_msec(void);
size_t	ft_time_diff_msec(size_t start, size_t end);
size_t	ft_time_diff_usec(size_t start, size_t end);
void	ft_time_usleep(size_t sleep);
void	ft_free_philos(t_philo ***philos, int n);
void	*ft_dining_philo(void *vars);
void	*ft_monitor_philos(void *vars);

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
