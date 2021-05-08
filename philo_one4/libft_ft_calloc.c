/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 02:38:59 by tayamamo          #+#    #+#             */
/*   Updated: 2021/05/06 02:40:13 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
