/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:25:13 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/16 15:30:15 by tayamamo         ###   ########.fr       */
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

# define THREADSLIMIT	200
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

struct	s_global;

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
	size_t			time_limit;
	size_t			last_eat;
	int				left_fork;
	int				right_fork;
	int				eat_cnt;
	struct s_global	*global;
	pthread_mutex_t	m_time_limit;
	pthread_mutex_t	m_eat_cnt;
}	t_philo;

typedef struct s_global
{
	size_t			start_time;
	t_arg			*args;
	t_philo			*philos;
	int				someone_is_dead;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_message;
	pthread_mutex_t	m_someone_is_deat;
	pthread_mutex_t	m_done;
}	t_global;

int		ft_check_arg(int argc, char *argv[]);
int		ft_check_int(char *argv);
int		ft_init_args(t_arg *args, int argc, char *argv[]);
int		ft_init_global(t_global *global, t_arg *args);
void	*thread_dining_philo(void *arg);
void	*thread_monitor_death(void *arg);
void	*thread_monitor_eat_cnt(void *arg);
int		ft_destroy_free(t_global *global, t_arg args);
int		ft_put_err(const char *err);
void	ft_put_message(t_philo *philo, int type);

size_t	ft_get_time_usec(void);
size_t	ft_get_time_msec(void);
void	ft_usleep(size_t sleep);

size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *s);
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_max(int a, int b);

#endif
