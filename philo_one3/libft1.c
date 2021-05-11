/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:14:46 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/11 12:15:29 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t cnt, size_t size)
{
	void	*ptr;

	if (cnt == 0 || size == 0)
	{
		cnt = 1;
		size = 1;
	}
	ptr = malloc(cnt * size);
	if (ptr)
		ft_bzero(ptr, cnt * size);
	return (ptr);
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int	ft_isspace(int c)
{
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

void	*ft_memset(void *dst, int val, size_t n)
{
	unsigned char	*p;
	unsigned char	c;

	p = dst;
	c = val;
	while (n--)
		*(p++) = c;
	return (dst);
}
