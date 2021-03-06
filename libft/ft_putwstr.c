/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 10:43:14 by mdubus            #+#    #+#             */
/*   Updated: 2017/01/12 14:37:44 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putwstr(wchar_t *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putwchar(str[i]);
		i++;
	}
}
