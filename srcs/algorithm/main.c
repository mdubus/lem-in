/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:24:26 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/13 13:27:00 by mdubus           ###   ########.fr       */
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

static int	start_related_to_end(t_lemin *l, int room, int *j)
{
int	i;

i = 0;
	while (i < l->nb_rooms && l->flag_start_to_end == 0)
	{
		if (l->pipes[room][i] == 1)
		{
			(*j)++;
			if (room != l->room_start)
			{
				l->lookup[room] = (*j - 1);
			}
			l->pipes[room][i] = 0;
			l->pipes[i][room] = 0;
			if (i == l->room_end)
			{
				l->flag_start_to_end = 1;
				(l->nb_path)++;
				l->pipes[room][i] = 1;
				l->pipes[i][room] = 1;
				(*j)--;
				l->lookup[room] = -1;
			}
			else if (l->lookup[i] > 0 || i == l->room_start)
			{
				(*j)--;
				l->lookup[room] = -1;
				l->pipes[room][i] = 1;
				l->pipes[i][room] = 1;
			}
			else
			{
				start_related_to_end(l, i, j);
				l->pipes[room][i] = 1;
				l->pipes[i][room] = 1;
				(*j)--;
				l->lookup[room] = -1;
			}
		}
		i++;
	}
	return (l->flag_start_to_end);
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
	update_sum_tab(&l);
	if (l.sum[l.room_start] == 0)
	{
		free_check_if_room(&l,
				"\033[091mErreur : La salle de depart n'est reliee a aucune autre salle\033[0m");
	}
	if (l.sum[l.room_end] == 0)
	{
		free_check_if_room(&l,
				"\033[091mErreur : La salle de fin n'est reliee a aucune autre salle\033[0m");
	}



	int i = 0;
	l.lookup = (int *)malloc(sizeof(int) * (unsigned long)(l.nb_rooms));
	while (i < l.nb_rooms)
		l.lookup[i++] = -1;
	start_related_to_end(&l, l.room_start, 0);
	free(l.lookup);




	bfs(&l, l.room_start);
	bfs(&l, l.room_end);
	update_sum_tab(&l);
	check_for_isolated_rooms(&l);
	if (l.graph == 1)
		export_graph(l.pipes, &l);

if (l.debug == 1)
	{
		print_resume(&l);
		print_equivalence_tab(&l);
		ft_print_tab_pipes(&l);
	}

//	count_nb_paths(&l);
//	if (l.debug == 1)
//		print_possible_paths(&l);


	free(l.sum);
	ft_memdel((void**)&l.string_file);
	ft_free_double_tab((void**)l.file);
	ft_free_double_tab((void**)l.eq);
	ft_free_double_tab((void**)l.pipes);
	free_lst_name(&l);

	return (0);
}
