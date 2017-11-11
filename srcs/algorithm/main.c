/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:24:26 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/11 19:03:23 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	free_check_if_room(t_lemin *l, char *str)
{
	free(l->string_file);
	ft_free_double_tab((void**)l->file);
	free_lst_name(l);
	error_lem_in(ft_putendl_fd, str, STDERR_FILENO, l);
}



void	make_tab_equivalence(t_lemin *l);
void	make_tab_equivalence(t_lemin *l)
{
	l->eq = (char **)malloc(sizeof(char*) * (unsigned long)(l->nb_rooms + 1));
	if (l->eq == NULL)
		free_check_if_room(l,
				"\033[091mErreur lors d'une allocation memoire\033[0m");
	l->room = l->begin;
	while (l->room != NULL)
	{
		l->eq[l->room->id] = ft_strdup(l->room->name);
		l->room = l->room->next;
	}
	l->room = l->begin;
	l->eq[l->nb_rooms] = NULL;
}

void	print_sum_table(t_lemin *l);
void	print_sum_table(t_lemin *l)
{
	ft_putchar('\n');
	int i = 0;
	while (i < l->nb_rooms)
		printf("%d\n", l->sum[i++]);
}


int	main(int argc, char **argv)
{
	t_lemin	l;


	init_struct_lemin(&l);
	init_arguments(argc, argv, &l);
	get_file(&l);
	ft_putendl(l.string_file);

	//parsing
	parsing_ants_number(&l);
	if (parsing_room_and_stock(&l) == 2)
		free_check_if_room(&l,
				"\033[091mErreur : La map est mal formatee\033[0m");
	make_tab_equivalence(&l);


	parsing_pipes_and_stock(&l);


	check_end_and_start(&l);

	// resolve
	create_sum_tab(&l);
	if (l.debug == 1)
	{
		print_resume(&l);
		print_equivalence_tab(&l);
		ft_print_tab_pipes(&l);
	}
	check_for_isolated_rooms(&l);

	count_nb_paths(&l);


	free(l.sum);
	ft_memdel((void**)&l.string_file);
	ft_free_double_tab((void**)l.file);
	ft_free_double_tab((void**)l.eq);
	ft_free_double_tab((void**)l.pipes);
	free_lst_name(&l);

	return (0);
}
