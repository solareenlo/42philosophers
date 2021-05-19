/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:12:59 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/19 16:00:23 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>

# ifndef __LINUX__
#  include <sys/time.h>
#  include <unistd.h>
#  include <sys/wait.h>
#  include <fcntl.h>
# endif

# define THREADSLIMIT	200
# define NEXTTHREAD		100
# define ONECYCLE		1000
# define TIMEMIN		60
# define TIMEMAX		10000
# define INTMAX			2147483647

# define SEMNAMESIZE	128
# define SEM			"ph_sem"
# define SEMFORKS		"forks"
# define SEMEATCNT		"eat_cnt"
# define SEMMESSAGE		"message"
# define SEMDONE		"done"
# define SEMTHEEND		"the_end"

# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define BLUE			"\033[0;34m"
# define PURPLE			"\033[0;35m"
# define CYAN			"\033[0;36m"
# define RESET			"\033[0m"

typedef enum e_type
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIED,
	DONE
}	t_type;

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
	pid_t			pid;
	int				pos;
	size_t			time_limit;
	size_t			last_eat;
	int				left_fork;
	int				right_fork;
	int				eat_cnt;
	struct s_global	*global;
	sem_t			*sem;
}	t_philo;

typedef struct s_global
{
	size_t	start_time;
	t_arg	*args;
	t_philo	*philos;
	int		the_end;
	sem_t	*sem_forks;
	sem_t	*sem_eat_cnt;
	sem_t	*sem_message;
	sem_t	*sem_done;
	sem_t	*sem_the_end;
}	t_global;

int		ph_check_arg(int argc, char *argv[]);
int		ph_check_int(char *argv);
int		ph_init_args(t_arg *args, int argc, char *argv[]);
int		ph_init_global(t_global *global, t_arg *args);

int		ph_put_message(t_philo *philo, int type);
int		ph_put_err(const char *err);

sem_t	*ph_sem_open(char *name, int value);
char	*ph_sem_create_name(char *dst, char *name, int nbr);
int		ph_sem_unlink_free(t_global *global, t_arg args);

int		ph_kill_processes(t_global *global, int cnt);
void	ph_wait_processes(t_global *global, t_arg args);

void	*process_dining_philo(t_philo *philo);
void	*thread_monitor_death(void *arg);
void	*thread_monitor_eat_cnt(void *arg);

size_t	ph_get_time_usec(void);
size_t	ph_get_time_msec(void);
void	ph_usleep(size_t sleep);

size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dlen);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *s);
char	*ft_itoa(int n);
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_max(int a, int b);
int		ft_atoi(const char *s);

#endif
