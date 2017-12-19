/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:13:24 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:13:25 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	print_head(int x)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_putstr("     ");
	while (i < x)
	{
		ft_putnbr(i++);
		ft_putchar(' ');
		if (i < 10)
			ft_putchar(' ');
	}
	ft_putstr(" \n     ");
	i = 0;
	while (i++ < x)
	{
		if (i < 9)
			ft_putstr("-  ");
		else if (i == 9)
			ft_putstr("- ");
		else
			ft_putstr("-- ");
	}
	ft_putchar('\n');
}

static void	print_body(t_lemin *l, int i)
{
	int j;

	j = 0;
	while (j < l->nb_rooms)
	{
		if (l->pipes[i][j] == 0)
		{
			ft_putstr("\033[090m");
			ft_putnbr(l->pipes[i][j++]);
			ft_putstr("  \033[0m");
		}
		else if (l->pipes[i][j] == 1)
		{
			ft_putstr("\033[092m");
			ft_putnbr(l->pipes[i][j++]);
			ft_putstr("  \033[0m");
		}
	}
	ft_putstr(" ");
}

void		ft_print_tab_pipes(t_lemin *l)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_putstr("\033[94m---------- Relations entre les pipes");
	ft_putendl("----------\n\033[0m");
	print_head(l->nb_rooms);
	while (i < l->nb_rooms)
	{
		ft_putnbr(i);
		if (i < 10)
			ft_putstr("  ");
		else
			ft_putchar(' ');
		ft_putstr("| ");
		print_body(l, i);
		ft_putchar('\n');
		j = 0;
		i++;
	}
	ft_putchar('\n');
}
