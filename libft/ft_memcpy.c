/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 10:00:49 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/11 10:37:34 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t n_cpy;

	n_cpy = n;
	while (n--)
		((unsigned char*)dst++)[0] = ((unsigned char*)src++)[0];
	return (dst - n_cpy);
}
