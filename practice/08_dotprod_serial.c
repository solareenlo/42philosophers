#include <stdlib.h>
#include <stdio.h>
#define VECLEN 100

typedef struct s_data
{
	double	*a;
	double	*b;
	double	sum;
	int		veclen;
}	t_data;

t_data	dotstr;

void	_dotprod()
{
	int		start, end, i;
	double	mysum, *x, *y;

	start = 0;
	end = dotstr.veclen;
	x = dotstr.a;
	y = dotstr.b;
	mysum = 0;
	i = start;
	while (i < end)
	{
		mysum += x[i] * y[i];
		i++;
	}
	dotstr.sum = mysum;
}

int	main(void)
{
	int		i, len;
	double	*a, *b;

	len = VECLEN;
	a = (double *)malloc(len * sizeof(double));
	b = (double *)malloc(len * sizeof(double));
	i = 0;
	while (i < len)
	{
		a[i] = 1;
		b[i] = a[i];
		i++;
	}
	dotstr.veclen = len;
	dotstr.a = a;
	dotstr.b = b;
	dotstr.sum = 0;
	_dotprod();
	printf("SUm = %f\n", dotstr.sum);
	free(a);
	free(b);
	return (0);
}
