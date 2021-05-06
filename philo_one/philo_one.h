/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:07:43 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/06 10:04:57 by tayamamo         ###   ########.fr       */
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
	size_t	start_time;
	int		number_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_ot_times_each_philo_must_eat;
}	t_arg;

typedef struct s_philo
{
	t_arg			*args;
	pthread_t		thread;
	size_t			last_time;
	int				id;
	int				cnt;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*m_cnt;
}	t_philo;

typedef struct s_monitor
{
	t_arg			*args;
	t_philo			*philos;
	pthread_t		thread;
	pthread_mutex_t	m_status;
}	t_monitor;

int				ft_putargerr(void);
size_t			ft_get_time_usec(void);
int				ft_check_arg(int argc, char *argv[]);
int				ft_check_int(char *argv);
pthread_mutex_t	*ft_init_mutex(int n);
int				ft_set_args(t_arg *args, int argc, char *argv[]);
int				ft_set_forks(pthread_mutex_t **forks, int n);
void			ft_putargs(t_arg args);
int				ft_set_philo(t_philo *philo, t_arg args);
int				ft_atoi(const char *s);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t cnt, size_t size);
int				ft_isdigit(int c);
int				ft_isspace(int c);
void			*ft_memset(void *dst, int val, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
size_t			ft_strlen(const char *s);

#endif
