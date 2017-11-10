/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:37:54 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/10 18:46:58 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_print_tab_int(int **tab, int x)
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
