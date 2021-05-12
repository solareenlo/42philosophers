/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:07:43 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/12 20:22:49 by tayamamo         ###   ########.fr       */
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

# define THREADSLIMIT	350
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
	t_arg			*args;
	struct s_global	*global;
	size_t			last_eat;
	size_t			limit;
	int				pos;
	int				cnt;
	int				done;
	int				right_fork;
	int				left_fork;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_global
{
	size_t			start_time;
	t_arg			*args;
	t_philo			*philos;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_message;
	pthread_mutex_t	m_died;
}	t_global;

int		ft_check_arg(int argc, char *argv[]);
int		ft_check_int(char *argv);
int		ft_init_args(t_arg *args, int argc, char *argv[]);
int		ft_init_philos(t_arg *args, t_global *global);
int		ft_init_global(t_arg *args, t_global *global);
void	*ft_dining_philo(void *arg);
void	ft_put_args(t_arg args);
void	ft_put_message(t_philo *philo, int type);
int		ft_put_err(const char *err);
int		ft_destory_free(t_arg args, t_global *global);

size_t	ft_get_time_usec(void);
size_t	ft_get_time_msec(void);
void	ft_usleep(size_t sleep);

int		ft_atoi(const char *s);
int		ft_isdigit(int c);
int		ft_isspace(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);

#endif
