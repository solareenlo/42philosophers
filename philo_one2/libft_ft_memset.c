/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 02:07:44 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/06 02:09:01 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
