/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:05:39 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/04 03:59:08 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static unsigned long	set_res(int neg_any_cutlim[3], unsigned long res)
{
	if (neg_any_cutlim[1] < 0)
	{
		if (neg_any_cutlim[0])
			res = 0x8000000000000000;
		else
			res = 0x7FFFFFFFFFFFFFFF;
	}
	else if (neg_any_cutlim[0])
		res = -res;
	return (res);
}

static void	check2(int *c, int *neg_any_cutlim,
		unsigned long *res, unsigned long *cutoff)
{
	if (neg_any_cutlim[1] < 0 || *res > *cutoff
		|| (*res == *cutoff && *c > neg_any_cutlim[2]))
		neg_any_cutlim[1] = -1;
	else
	{
		neg_any_cutlim[1] = 1;
		*res *= 10;
		*res += *c;
	}
}

static void	check1(int *neg_any_cutlim, int *c, const char **s,
		unsigned long *cutoff)
{
	neg_any_cutlim[0] = 0;
	*c = *((*s)++);
	while (ft_isspace(*c))
		*c = *((*s)++);
	if (*c == '-')
	{
		neg_any_cutlim[0] = 1;
		*c = *((*s)++);
	}
	else if (*c == '+')
		*c = *((*s)++);
	if (neg_any_cutlim[0])
		*cutoff = -(unsigned long) 0x8000000000000000;
	else
		*cutoff = 0x7FFFFFFFFFFFFFFF;
	neg_any_cutlim[2] = *cutoff % (unsigned long) 10;
	*cutoff /= (unsigned long) 10;
}

int	ft_atoi(const char *s)
{
	unsigned long	res;
	int				c;
	unsigned long	cutoff;
	int				neg_any_cutlim[3];

	check1(neg_any_cutlim, &c, &s, &cutoff);
	res = 0;
	neg_any_cutlim[1] = 0;
	while (1)
	{
		if (ft_isdigit(c))
			c -= '0';
		else
			break ;
		check2(&c, neg_any_cutlim, &res, &cutoff);
		c = *(s++);
	}
	res = set_res(neg_any_cutlim, res);
	return ((int)res);
}
