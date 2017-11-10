/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab_bool.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:47:06 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/10 18:48:31 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_print_tab_bool(bool **tab, int x)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < x)
	{
		while (j < x)
		{
			ft_putnbr(tab[i][j++]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
		j = 0;
		i++;
	}
}
