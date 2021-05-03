#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM 4

void	*_busy_work(void *t)
{
	int		i;
	long	tid;
	double	res = 0.0;

	tid = (long)t;
	printf("Thraed %ld starting...\n", tid);
	i = 0;
	while (i < (int)1e6)
	{
		res += sin(i) * tan(i);
		i++;
	}
	printf("Thread %ld done. res = %e\n", tid, res);
	pthread_exit((void *)t);
}

int	main(void)
{
	pthread_t		threads[NUM];
	pthread_attr_t	attr;
	int				ret;
	long			i;
	void			*status;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	i = 0;
	while (i < NUM)
	{
		printf("Main: creating thread %ld\n", i);
		ret = pthread_create(&threads[i], &attr, _busy_work, (void *)i);
		if (ret)
		{
			printf("ERROR: return code from pthread_creat() is %d\n", ret);
			exit(1);
		}
		i++;
	}
	pthread_attr_destroy(&attr);
	i = 0;
	while (i < NUM)
	{
		ret = pthread_join(threads[i], &status);
		if (ret)
		{
			printf("ERROR: return code from pthread_creat() is %d\n", ret);
			exit(1);
		}
		printf("Main: completed join with thread %ld having a status of %ld\n",
				i, (long)status);
		i++;
	}
	printf("Main: program completed. Exiting.\n");
	pthread_exit(NULL);
	return (0);
}
