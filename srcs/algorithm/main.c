/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:24:26 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/10 21:23:33 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	init_struct_lemin(t_lemin *l);
void	init_struct_lemin(t_lemin *l)
{
	l->nb_ants = 0;
	l->nb_pipes = 0;
	l->nb_rooms = 0;
	l->flag_start = -1;
	l->flag_end = -1;
	l->id = 0;
	l->comments = 0;
	l->commands = 0;
	l->start = 0;
	l->pipes = NULL;
	l->string_file = NULL;
	l->room_start = -1;
	l->room_end = -1;
	l->file = NULL;
	l->room = NULL;
	l->begin = NULL;
	l->sum = NULL;
	l->nb_path = 0;
	l->lookup = NULL;
}


void	free_check_if_room(t_lemin *l, char *str)
{
	free(l->string_file);
	ft_free_double_tab((void**)l->file);
	free_lst_name(l);
	error_lem_in(ft_putendl_fd, str, STDERR_FILENO);
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


int	main(void)
{
	t_lemin	l;

	init_struct_lemin(&l);
	get_file(&l);
	ft_putendl(l.string_file);

	//parsing
	parsing_ants_number(&l);
	if (parsing_room_and_stock(&l) == 2)
		free_check_if_room(&l,
				"\033[091mErreur : La map est mal formatee\033[0m");
	make_tab_equivalence(&l);
	print_equivalence_tab(&l);
	ft_putchar('\n');

	parsing_pipes_and_stock(&l);
//	ft_print_tab_int(l.pipes, l.nb_rooms);
//	ft_putchar('\n');
	check_end_and_start(&l);

	// resolve
	create_sum_tab(&l);
//	print_sum_table(&l);
//	ft_putendl("remove isolated rooms");
	check_for_isolated_rooms(&l);
//	printf("nb_rooms = %d\n\n", l.nb_rooms);

//	ft_putendl("count nb paths");
	count_nb_paths(&l);
//	ft_putendl("malloc");
//	int	**test;
	


/*
	ft_print_tab_int(l.pipes, l.nb_rooms);
	ft_putchar('\n');


	printf("\nid start = %d, id end = %d\n", l.room_start, l.room_end);
*/
	free(l.sum);
	ft_memdel((void**)&l.string_file);
	ft_free_double_tab((void**)l.file);
	ft_free_double_tab((void**)l.eq);
	ft_free_double_tab((void**)l.pipes);
	free_lst_name(&l);


	return (0);
}
