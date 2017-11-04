/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_if_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 18:42:44 by mdubus            #+#    #+#             */
/*   Updated: 2017/10/31 18:43:48 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_check_if_num(char	*str)
{
	int	i;
	int	isnum;

	i = 0;
	isnum = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i++]) == 0)
			isnum = 1;
	}
	return (isnum);
}
