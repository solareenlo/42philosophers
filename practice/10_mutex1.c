#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#define LOOPMAX 65535

pthread_mutex_t	m;
int				cnt;

void	f1();
void	f2();

int	main(void)
{
	pthread_t	threads[2];
	int			ret[2];

	pthread_mutex_init(&m, NULL);
	ret[0] = pthread_create(&threads[0], NULL, (void *)f1, NULL);
	ret[1] = pthread_create(&threads[1], NULL, (void *)f1, NULL);
	if (ret[0])
	{
		printf("ERROR: return code from pthread_creat() is %d\n", ret[0]);
		exit(1);
	}
	if (ret[1])
	{
		printf("ERROR: return code from pthread_creat() is %d\n", ret[1]);
		exit(1);
	}
	printf("Execute pthread_join thread1\n");
	ret[0] = pthread_join(threads[0], NULL);
	if (ret[0])
	{
		printf("ERROR: return code from pthread_join() is %d\n", ret[0]);
		exit(1);
	}
	ret[1] = pthread_join(threads[1], NULL);
	if (ret[1])
	{
		printf("ERROR: return code from pthread_join() is %d\n", ret[1]);
		exit(1);
	}
	printf("Done\n%d\n", cnt);
	pthread_mutex_destroy(&m);
	return (0);
}

void	f1()
{
	size_t	i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < LOOPMAX)
	{
		ret = pthread_mutex_lock(&m);
		if (ret)
		{
			printf("ERROR: return code from pthread_mutex_lock() is %d\n", ret);
			exit(1);
		}
		cnt++;
		ret = pthread_mutex_unlock(&m);
		if (ret)
		{
			printf("ERROR: return code from pthread_mutex_unlock() is %d\n", ret);
			exit(1);
		}
		i++;
	}
}

void	f2()
{
	size_t	i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < LOOPMAX)
	{
		ret = pthread_mutex_lock(&m);
		if (ret)
		{
			printf("ERROR: return code from pthread_mutex_lock() is %d\n", ret);
			exit(1);
		}
		cnt++;
		ret = pthread_mutex_unlock(&m);
		if (ret)
		{
			printf("ERROR: return code from pthread_mutex_unlock() is %d\n", ret);
			exit(1);
		}
		i++;
	}
}
