#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM 8

void	*_print_hello(void *id)
{
	long	taskid;

	sleep(1);
	taskid = *(long *)id;
	printf("Hello from thread %ld\n", taskid);
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t	threads[NUM];
	int			ret;
	int			i;

	i = 0;
	while (i < NUM)
	{
		printf("Creating thread %d\n", i);
		ret = pthread_create(&threads[i], NULL, _print_hello, &i);
		if (ret)
		{
			printf("ERROR: return code from pthread_creat() is %d\n", i);
			exit(1);
		}
		i++;
	}
	return (0);
}
