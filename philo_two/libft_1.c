/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:30:08 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/17 20:48:42 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	slen;
	size_t	dlen;
	char	*d;
	int		i;

	d = dst;
	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	if (size <= dlen)
		return (size + slen);
	i = 0;
	while (src[i] != '\0' && dlen + 1 < size)
	{
		dst[dlen] = src[i];
		i++;
		dlen++;
	}
	dst[dlen] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dlen)
{
	size_t	slen;

	if (!dst || !src)
		return (0);
	slen = ft_strlen(src);
	if (slen + 1 < dlen)
		ft_memcpy(dst, src, slen + 1);
	else if (dlen != 0)
	{
		ft_memcpy(dst, src, dlen - 1);
		dst[dlen - 1] = '\0';
	}
	return (slen);
}
