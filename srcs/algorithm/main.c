/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:24:26 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/17 13:30:49 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"

void	free_check_if_room(t_lemin *l, char *str)
{
	free(l->string_file);
	ft_free_double_tab((void**)l->file);
	free_lst_name(l);
	error_lem_in(ft_putendl_fd, str, STDERR_FILENO, l);
}


int	main(int argc, char **argv)
{
	t_lemin	l;


	init_struct_lemin(&l);
	init_arguments(argc, argv, &l);

	//parsing
	parsing(&l);


	// resolve

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

	free(l.sum);
	ft_memdel((void**)&l.string_file);
	ft_free_double_tab((void**)l.file);
	ft_free_double_tab((void**)l.eq);
	ft_free_double_tab((void**)l.pipes);
	t_path	*temp;

	temp = NULL;
	l.solution = l.solution_begin;
	while (l.solution)
	{
		temp = l.solution;
		l.solution = l.solution->next;
		ft_memdel((void**)&temp->path);
		ft_memdel((void**)&temp);
	}
	free(l.sorted);
	free_lst_name(&l);

	return (0);
}
