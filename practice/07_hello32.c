#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#define NUM 32

void	*_print_hello(void *id)
{
	int		i;
	double	res = 0;

	sleep(3);
	i = 0;
	while (i < 1000)
	{
		res += sin(i) + tan(i);
		i++;
	}
	printf("%ld Hello World!\n", *(long *)id);
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t	threads[NUM];
	int			ret;
	long		i;

	i = 0;
	while (i < NUM)
	{
		ret = pthread_create(&threads[i], NULL, _print_hello, (void *)i);
		if (ret)
		{
			printf("ERROR: return code from pthread_creat() is %d\n", ret);
			printf("Code %d = %s\n", ret, strerror(ret));
			exit(1);
		}
		i++;
	}
	printf("main(): Created %ld threads.\n", i);
	pthread_exit(NULL);
	return(0);
}
