#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM 8

char	*messages[NUM];

typedef struct	s_thrad_tada
{
	int		thread_id;
	int		sum;
	char	*message;
}	t_thread_data;

t_thread_data	thread_data_array[NUM];

void	*_printf_hello(void	*thread_arg)
{
	int				taskid;
	int				sum;
	char			*message;
	t_thread_data	*my_data;

	sleep(1);
	my_data = (t_thread_data *)thread_arg;
	taskid = my_data->thread_id;
	sum = my_data->sum;
	message = my_data->message;
	printf("Thread %d: %s sum = %d\n", taskid, message, sum);
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t	threads[NUM];
	int			ret;
	int			i;
	int			sum;

	sum = 0;
	messages[0] = "English: Hello World!";
	messages[1] = "French: Bonjour, le monde!";
	messages[2] = "Spanish: Hola al mundo";
	messages[3] = "Klingon: Nuq neH!";
	messages[4] = "German: Guten Tag, Welt!";
	messages[5] = "Russian: Zdravstvytye, mir!";
	messages[6] = "Japan: Sekai e konnichiwa!";
	messages[7] = "Latin: Orbis, te saluto!";
	i = 0;
	while (i < NUM)
	{
		sum += i;
		thread_data_array[i].thread_id = i;
		thread_data_array[i].sum = sum;
		thread_data_array[i].message = messages[i];
		printf("Creating thread %d\n", i);
		ret = pthread_create(&threads[i], NULL, _printf_hello, (void *)&thread_data_array[i]);
		if (ret)
		{
			printf("ERROR: return code from pthread_creat() is %d\n", ret);
			exit(1);
		}
		i++;
	}
	pthread_exit(NULL);
	return (0);
}
