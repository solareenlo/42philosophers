/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:25:13 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/12 22:18:21 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# ifndef __LINUX__
#  include <sys/time.h>
#  include <unistd.h>
# endif

# define THREADSLIMIT	300
# define INTMAX			2147483647
# define FORK			0x001
# define EAT			0x002
# define SLEEP			0x004
# define THINK			0x008
# define DIED			0x010
# define DONE			0x020
# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define BLUE			"\033[0;34m"
# define PURPLE			"\033[0;35m"
# define CYAN			"\033[0;36m"
# define RESET			"\033[0m"

typedef struct s_arg
{
	int		number_of_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		number_of_times_each_philo_must_eat;
}	t_arg;

typedef struct s_philo
{
	int				pos;
	int				done;
	size_t			last_eat;
	pthread_mutex_t	m_eating;
	pthread_t		thread;
	pthread_t		monitor;
}	t_philo;

typedef struct s_global
{
	t_arg			*args;
	t_philo			*philos;
	size_t			start_time;
	int				total_eat;
	int				done;
	pthread_mutex_t	m_picking;
	pthread_mutex_t	m_message;
	pthread_mutex_t	*m_forks;
}	t_global;

int		ft_check_arg(int argc, char *argv[]);
int		ft_check_int(char *argv);
int		ft_init_args(t_arg *args, int argc, char *argv[]);
int		ft_init_philos(t_global *global, t_arg *args);
int		ft_free_destroy(t_global *global, t_arg *args);
int		ft_put_err(const char *err);

size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *s);
int		ft_isdigit(int c);
int		ft_isspace(int c);

#endif
