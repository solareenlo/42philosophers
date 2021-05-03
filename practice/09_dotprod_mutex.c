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

t_data			dotstr;
pthread_t		callthd[NUMTHREADS];
pthread_mutex_t	mutexsum;

void	*_dotprod(void *arg)
{
	int		i, start, end, len;
	long	offset;
	double	mysum, *x, *y;

	offset = (long)arg;
	len = dotstr.veclen;
	start = offset * len;
	end = start + len;
	x = dotstr.a;
	y = dotstr.b;
	mysum = 0;
	i = 0;
	while (i < end)
	{
		mysum += x[i] * y[i];
		i++;
	}
	pthread_mutex_lock(&mutexsum);
	dotstr.sum += mysum;
	printf("Thread %ld did %3d to %d: mysum=%f global sum = %f\n",
			offset, start, end, mysum, dotstr.sum);
	pthread_mutex_unlock(&mutexsum);
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
	dotstr.veclen = VECLEN;
	dotstr.a = a;
	dotstr.b = b;
	dotstr.sum = 0;
	pthread_mutex_init(&mutexsum, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	i = 0;
	while (i < NUMTHREADS)
	{
		pthread_create(&callthd[i], &attr, _dotprod, (void *)i);
		i++;
	}
	pthread_attr_destroy(&attr);
	i = 0;
	while (i < NUMTHREADS)
	{
		pthread_join(callthd[i], &status);
		i++;
	}
	printf("Sum = %f\n", dotstr.sum);
	free(a);
	free(b);
	pthread_mutex_destroy(&mutexsum);
	pthread_exit(NULL);
	return (0);
}
