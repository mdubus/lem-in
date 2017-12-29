/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_latoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 10:46:23 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/28 13:22:45 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	check_pos(const char *str, int j)
{
	if (str[j + 1] < '0' && (str[j + 1] > '9'))
		return (0);
	if ((str[j] == '+') && (ft_isdigit(str[j + 1])))
		j++;
	return (j);
}

static int	check_beginning(const char *str, int j)
{
	while ((str[j] == 32) || (str[j] >= 9 && str[j] <= 13))
		j++;
	return (j);
}

static long	do_atoi(const char *str, long i, int j)
{
	while (str[j] >= '0' && str[j] <= '9')
	{
		i = i * 10 + (str[j]) - '0';
		j++;
	}
	return (i);
}

long		ft_latoi(const char *str)
{
	long	i;
	int		j;
	int		sign;

	i = 0;
	j = 0;
	sign = 1;
	j = check_beginning(str, j);
	if ((str[j] == '-'))
	{
		if ((ft_isdigit(str[j + 1])) && (ft_isdigit(str[j - 1]) == 0))
		{
			sign = -1;
			j++;
		}
		if ((ft_isdigit(str[j + 1])) && (ft_isdigit(str[j - 1]) != 0))
			return (i);
	}
	if (str[j] == '+')
		j = check_pos(str, j);
	i = do_atoi(str, i, j);
	return (i * sign);
}
