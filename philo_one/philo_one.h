/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:07:43 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/07 05:21:04 by tayamamo         ###   ########.fr       */
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
	pthread_t		thread;
	t_arg			*args;
	size_t			last_time;
	int				id;
	int				cnt;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*m_message;
	pthread_mutex_t	*m_done;
	pthread_mutex_t	*m_died;
}	t_philo;

typedef struct s_monitor
{
	pthread_t		thread;
	t_arg			*args;
	t_philo			**philos;
	pthread_mutex_t	m_message;
	pthread_mutex_t	*m_done;
	pthread_mutex_t	*m_died;
}	t_monitor;

int		ft_putargerr(void);
size_t	ft_get_time_usec(void);
int		ft_check_arg(int argc, char *argv[]);
int		ft_check_int(char *argv);
int		ft_set_args(t_arg *args, int argc, char *argv[]);
int		ft_set_forks(pthread_mutex_t **forks, int n);
int		ft_set_philos(t_philo ***philos, t_arg *args,
			pthread_mutex_t *forks);
int		ft_set_monitor(t_monitor *monitor, t_philo **philos,
			t_arg *args);
void	ft_putargs(t_arg args);
int		ft_run_philos(t_philo ***philos, t_monitor *monitor,
			t_arg args);
void	*ft_dining_philo(void *var);
void	ft_print_philo(t_philo *philo, int status);
void	*ft_mutex_put_message(t_philo *philo, int status);
void	ft_free_philos(t_philo ***philos, int n);

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
