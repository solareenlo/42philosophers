#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM	8

char	*messages[NUM];

void	*_print_hello(void	*id)
{
	long	taskid;

	sleep(1);
	taskid = (long)id;
	printf("Thread %ld: %s\n", taskid, messages[taskid]);
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t	threads[NUM];
	long		taskids[NUM];
	int			ret;
	int			i;

	messages[0] = "English: Hello World!";
	messages[1] = "French: Bonjour, le monde!";
	messages[2] = "Spanish: Hola al mundo";
	messages[3] = "Klingon: Nuq neH!";
	messages[4] = "German: Guten Tag, Welt!";
	messages[5] = "Russian: Zdravstvuyte, mir!";
	messages[6] = "Japan: Sekai e konnichiwa!";
	messages[7] = "Latin: Orbis, te saluto!";
	i = 0;
	while (i < NUM)
	{
		taskids[i] = i;
		printf("Creating thread %d\n", i);
		ret = pthread_create(&threads[i], NULL, _print_hello, (void *)taskids[i]);
		if (ret)
		{
			printf("ERROR: return code from pthread_create() is %d\n", ret);
			exit(1);
		}
		i++;
	}
	pthread_exit(NULL);
	return (0);
}
