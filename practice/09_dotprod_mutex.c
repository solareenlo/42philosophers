#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUMTHREADS 4
#define VECLEN 100

typedef struct s_data
{
	double	*a;
	double	*b;
	double	sum;
	int		veclen;
}	t_data;

t_data			g_dotstr;
pthread_t		g_callthd[NUMTHREADS];
pthread_mutex_t	g_mutexsum;

void	*_dotprod(void *arg)
{
	int		i, start, end, len;
	long	offset;
	double	mysum, *x, *y;

	offset = (long)arg;
	len = g_dotstr.veclen;
	start = offset * len;
	end = start + len;
	x = g_dotstr.a;
	y = g_dotstr.b;
	mysum = 0;
	i = 0;
	while (i < end)
	{
		mysum += x[i] * y[i];
		i++;
	}
	pthread_mutex_lock(&g_mutexsum);
	g_dotstr.sum += mysum;
	printf("Thread %ld did %3d to %d: mysum=%f global sum = %f\n",
			offset, start, end, mysum, g_dotstr.sum);
	pthread_mutex_unlock(&g_mutexsum);
	pthread_exit(NULL);
}

int	main(void)
{
	long			i;
	double			*a, *b;
	void			*status;
	pthread_attr_t	attr;

	a = (double *)malloc(NUMTHREADS * VECLEN * sizeof(double));
	b = (double *)malloc(NUMTHREADS * VECLEN * sizeof(double));
	i = 0;
	while (i < NUMTHREADS * VECLEN)
	{
		a[i] = 1;
		b[i] = a[i];
		i++;
	}
	g_dotstr.veclen = VECLEN;
	g_dotstr.a = a;
	g_dotstr.b = b;
	g_dotstr.sum = 0;
	pthread_mutex_init(&g_mutexsum, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	i = 0;
	while (i < NUMTHREADS)
	{
		pthread_create(&g_callthd[i], &attr, _dotprod, (void *)i);
		i++;
	}
	pthread_attr_destroy(&attr);
	i = 0;
	while (i < NUMTHREADS)
	{
		pthread_join(g_callthd[i], &status);
		i++;
	}
	printf("Sum = %f\n", g_dotstr.sum);
	free(a);
	free(b);
	pthread_mutex_destroy(&g_mutexsum);
	pthread_exit(NULL);
	return (0);
}
