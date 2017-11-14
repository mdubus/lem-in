/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:24:26 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/14 12:48:08 by mdubus           ###   ########.fr       */
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

static void	check_sum_end_start(t_lemin *l)
{
	if (l->sum[l->room_start] == 0)
	{
		free(l->sum);
		ft_memdel((void**)&l->string_file);
		ft_free_double_tab((void**)l->file);
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		free_lst_name(l);
		error_lem_in(ft_putendl_fd,
				"\033[091mErreur : La salle de depart n'est reliee a aucune autre salle\033[0m", STDERR_FILENO, l);
	}
	if (l->sum[l->room_end] == 0)
	{
		free(l->sum);
		ft_memdel((void**)&l->string_file);
		ft_free_double_tab((void**)l->file);
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		free_lst_name(l);
		error_lem_in(ft_putendl_fd,
				"\033[091mErreur : La salle de fin n'est reliee a aucune autre salle\033[0m", STDERR_FILENO, l);
	}
}

static void	find_best_paths(t_lemin *l)
{
	int	i;
	int	j;
	int	flag;
	t_path	*next;

	i = 1;
	j = 1;
	flag = 0;
	next = NULL;
	l->path = l->path_begin;
	if (l->path->next)
	{
		ft_putendl("COUCOU");
	next = l->path->next;
	while (next->next)
	{
		while (l->path->path[i] != l->room_end && flag == 0)
		{
			printf("room i = %d\n", l->path->path[i]);
			j = 1;
			while (next->path[j] != l->room_end && flag == 0)
			{
				if (l->path->path[i] == next->path[j])
					flag = 1;
				j++;
			}
			i++;
		}
		if (flag == 0)
			l->path->different_path += 1;
		if (next->next)
		{
			next = next->next;
			i = 1;
		}
	}
	}
	printf("different paths : %d\n", l->path->different_path);
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
	check_sum_end_start(&l);
	if (l.graph == 1)
		export_graph(l.pipes, &l);
	check_if_solution_exists(&l);
	bfs(&l, l.room_start);
	bfs(&l, l.room_end);
	update_sum_tab(&l);
	check_for_isolated_rooms(&l);
	count_nb_paths(&l);

	if (l.debug == 1)
	{
		print_resume(&l);
		print_equivalence_tab(&l);
		ft_print_tab_pipes(&l);
		print_possible_paths(&l);
	}

	find_best_paths(&l);







	free(l.sum);
	ft_memdel((void**)&l.string_file);
	ft_free_double_tab((void**)l.file);
	ft_free_double_tab((void**)l.eq);
	ft_free_double_tab((void**)l.pipes);
	free_lst_name(&l);

	return (0);
}
