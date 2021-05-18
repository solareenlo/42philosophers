/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_itoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:57:32 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/17 20:57:47 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	_set(char *s, int n, size_t cnt)
{
	long long	tmp;

	tmp = n;
	if (n < 0)
		tmp = -tmp;
	*(s + cnt) = '\0';
	if (n == 0)
	{
		*s = '0';
		return ;
	}
	cnt--;
	while (tmp)
	{
		*(s + cnt) = tmp % 10 + '0';
		tmp /= 10;
		cnt--;
	}
	if (n < 0)
		*s = '-';
}

char	*ft_itoa(int n)
{
	char		*res;
	long long	tmp;
	size_t		cnt;

	tmp = n;
	if (n < 0)
		tmp = -tmp;
	if (n <= 0)
		cnt = 1;
	else
		cnt = 0;
	while (tmp)
	{
		tmp /= 10;
		cnt++;
	}
	res = malloc(sizeof(char) * (cnt + 1));
	if (res == NULL)
		return (NULL);
	_set(res, n, cnt);
	return (res);
}
