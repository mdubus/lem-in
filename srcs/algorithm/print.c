/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:13:16 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/29 17:31:26 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void		print_resume(t_lemin *l)
{
	ft_putendl("\033[94m---------- Resume ----------\n\033[0m");
	ft_putstr("\033[095mNombre de fourmis : \033[0m");
	ft_putnbr(l->nb_ants);
	ft_putstr("\n\033[095mNombre de rooms : \033[0m");
	ft_putnbr(l->nb_rooms);
	ft_putstr("\n\033[095mNombre de pipes : \033[0m");
	ft_putnbr(l->nb_pipes);
	ft_putstr("\n\033[095mRoom de debut : \033[0m");
	ft_putstr(l->eq[l->room_start]);
	ft_putstr("\n\033[095mRoom de fin : \033[0m");
	ft_putstr(l->eq[l->room_end]);
	ft_putendl("\n");
}

void		print_equivalence_tab(t_lemin *l)
{
	int	i;

	i = 0;
	ft_putstr("\033[94m---------- Relations id | ");
	ft_putendl("nom de room ----------\n\033[0m");
	while (i < l->nb_rooms)
	{
		ft_putnbr(i);
		ft_putchar(' ');
		if (i < 10)
			ft_putchar(' ');
		ft_putstr("| ");
		ft_putstr(l->eq[i]);
		ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
}

void		print_result(t_lemin *l)
{
	int j;

	j = 0;
	ft_putendl("\033[94m---------- Chemins selectionnes ----------\n\033[0m");
	l->path = l->solution_begin;
	while (l->path)
	{
		j = 0;
		ft_putstr(l->eq[l->room_start]);
		ft_putstr("\033[090m -> \033[0m");
		while (l->path->path[j] != l->room_end)
		{
			ft_putstr(l->eq[l->path->path[j++]]);
			ft_putstr("\033[090m -> \033[0m");
		}
		ft_putstr(l->eq[l->room_end]);
		ft_putchar('\n');
		l->path = l->path->next;
	}
	ft_putchar('\n');
}

void		print_possible_paths(t_lemin *l)
{
	int j;

	j = 0;
	ft_putendl("\033[94m---------- Chemins possibles ----------\n\033[0m");
	ft_putstr("\033[095mNombre de chemins possibles : \033[0m");
	ft_putnbr(l->nb_path);
	ft_putendl("\n");
	l->path = l->path_begin;
	while (l->path)
	{
		j = 0;
		ft_putstr(l->eq[l->room_start]);
		ft_putstr("\033[090m -> \033[0m");
		while (l->path->path[j] != l->room_end)
		{
			ft_putstr(l->eq[l->path->path[j++]]);
			ft_putstr("\033[090m -> \033[0m");
		}
		ft_putstr(l->eq[l->room_end]);
		ft_putchar('\n');
		l->path = l->path->next;
	}
	ft_putchar('\n');
}
