/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:24:26 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/18 17:34:43 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"

static void	print_ants(t_lemin *l)
{
	int	i;

	i = 0;
	l->solution = l->solution_begin;
	while (l->solution)
	{
		l->nb_path_final++;
		l->solution = l->solution->next;
	}
	l->solution = l->solution_begin;
	while (i < l->nb_ants)
	{
		ft_putchar('L');
		ft_putchar('x');
		ft_putchar('-');
		ft_putchar('x');
		ft_putchar(' ');
		if ((i + 1) % l->nb_path_final == 0)
			ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
}

int	main(int argc, char **argv)
{
	t_lemin	l;


	init_struct_lemin(&l);
	init_arguments(argc, argv, &l);
	parsing(&l);
	remove_useless_paths(&l);

	if (l.debug == 1)
	{
		print_resume(&l);
		print_equivalence_tab(&l);
		ft_print_tab_pipes(&l);
		print_possible_paths(&l);
	}

	resolve(&l);

	if (l.debug == 1)
	{
		print_result(&l);
		ft_putendl("\033[94m---------- Resultat ----------\n\033[0m");
	}
	ft_putendl(l.string_file);


	print_ants(&l);

	free_at_end(&l);
	return (0);
}
