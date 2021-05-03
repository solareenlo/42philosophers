#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NTHREADS 4
#define N 100
#define MEGEXTRA 100000

pthread_attr_t	attr;

void	*dowork(void *threadid)
{
	double	A[N][N];
	int		i,j;
	long		tid;
	size_t	mystacksize;

	tid = (long)threadid;
	pthread_attr_getstacksize (&attr, &mystacksize);
	printf("Thread %ld: stack size = %li bytes \n", tid, mystacksize);
	i = 0;
	while (i < N)
	{
		j = 0;
		while (j < N)
		{
			A[i][j] = ((i*j)/3.452) + (N-i);
			j++;
		}
		i++;
	}
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t	threads[NTHREADS];
	size_t		stacksize;
	int			ret;
	long		i;

	pthread_attr_init(&attr);
	pthread_attr_getstacksize (&attr, &stacksize);
	printf("Default stack size = %li\n", stacksize);
	stacksize = sizeof(double) * N * N + MEGEXTRA;
	printf("Amount of stack needed per thread = %li\n", stacksize);
	pthread_attr_setstacksize (&attr, stacksize);
	printf("Creating threads with stack size = %li bytes\n", stacksize);
	i = 0;
	while (i < NTHREADS)
	{
		ret = pthread_create(&threads[i], &attr, dowork, (void *)i);
		if (ret){
			printf("ERROR; return code from pthread_create() is %d\n", ret);
			exit(-1);
		}
		i++;
	}
	printf("Created %ld threads.\n", i);
	pthread_exit(NULL);
	return (0);
}
