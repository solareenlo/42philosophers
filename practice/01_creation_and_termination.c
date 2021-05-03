#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void	*_print_hello(void *id)
{
	long	tid;

	tid = (long)id;
	printf("Hello world! It's me, thread %ld!\n", tid);
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t	threads[5];
	int			ret;
	long		t;

	t = 0;
	while (t < 5)
	{
		printf("In main: creating thread %ld\n", t);
		ret = pthread_create(&threads[t], NULL, _print_hello, (void *)(t-1));
		if (ret)
		{
			printf("ERROR: return code from pthread_create() is %d\n", ret);
			exit(1);
		}
		t++;
	}
	pthread_exit(NULL);
	return (0);
}
