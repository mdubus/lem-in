/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:24:26 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/16 17:36:41 by mdubus           ###   ########.fr       */
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

static void calculate_different_paths(t_lemin *l)
{
	int	i;
	int	j;
	int	flag;
	t_path	*next;

	i = 0;
	j = 0;
	flag = 0;
	next = NULL;
	l->path = l->path_begin;
	next = l->path;
	while (l->path)
	{
		while (next->next)
		{
			next = next->next;
			i = 0;
			while (l->path->path[i] != l->room_end && flag == 0)
			{
				j = 0;
				while (next->path[j] != l->room_end && flag == 0)
				{
					if (l->path->path[i] == next->path[j])
						flag = 1;
					j++;
				}
				i++;
			}
			if (flag == 0)
			{
				l->path->different_path += 1;
				int nbr_coups_min = l->path->nbr_coups + next->nbr_coups;
				if (l->path->nbr_coups_min == 0 || l->path->nbr_coups_min < nbr_coups_min)
					l->path->nbr_coups_min = nbr_coups_min;
				printf("coups min = %d\n", nbr_coups_min);
			}
			flag = 0;
		}
		l->path = l->path->next;
		next = l->path;
	}
}

static void	find_best_path(t_lemin *l)
{
	l->path = l->path_begin;
	int	nb_path;
	int	nbr_coups;

	nb_path = l->path->different_path;
	nbr_coups = l->path->nbr_coups;
	l->best_path = l->path;
	while (l->path)
	{
		if (l->path->different_path > nb_path)
		{
			nb_path = l->path->different_path;
			l->best_path = l->path;
		}
		else if (l->path->different_path == nb_path)
		{
			if (l->path->nbr_coups < nbr_coups)
			{
				nbr_coups = l->path->nbr_coups;
				l->best_path = l->path;
			}
		}
		l->path = l->path->next;
	}
}

static void	delete_other_paths(t_lemin *l)
{
	t_path	*prev;
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	l->path = l->path_begin;
	prev = l->path_begin;
	while (l->path)
	{
		if (l->path != l->best_path)
		{
			i = 0;
			while (l->best_path->path[i] != l->room_end && flag == 0)
			{
				j = 0;
				while (l->path->path[j] != l->room_end && flag == 0)
				{
					if (l->best_path->path[i] == l->path->path[j])
						flag = 1;
					j++;
				}
				i++;
			}
		}
		if (flag == 1)
		{
			if (l->path == l->path_begin)
			{
				l->path = l->path->next;
				free(prev->path);
				free(prev);
				prev = l->path;
				l->path_begin = l->path;
				prev = l->path;
			}
			else
			{
				prev->next = l->path->next;
				free(l->path->path);
				free(l->path);
				l->path = prev;
				prev = l->path;
				l->path = l->path->next;
			}
			flag = 0;
		}
		else
		{
			prev = l->path;
			l->path = l->path->next;
		}
	}
}

static void	put_best_path_in_result(t_lemin *l)
{
	t_path	*temp;

	l->path = l->path_begin;
	temp = l->path;
	while (l->path && l->path != l->best_path)
	{
		temp = l->path;
		l->path = l->path->next;
	}
	if (l->path == l->best_path)
	{
		if (l->solution == NULL)
		{
			l->solution = l->path;
			l->solution_begin = l->solution;
		}
		else
		{
			l->solution->next = l->path;
			l->solution = l->solution->next;
		}
		temp->next = l->path->next;
		if (l->path == l->path_begin)
			l->path_begin = l->path->next;
		l->solution->next = NULL;
	}
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

	print_possible_paths(&l);

	while (l.path_begin)
	{
		l.path = l.path_begin;
		while (l.path)
		{
			l.path->nbr_coups_min = 0;
			l.path->different_path = 0;
			l.path = l.path->next;
		}
		calculate_different_paths(&l);
		find_best_path(&l);
		delete_other_paths(&l);
		put_best_path_in_result(&l);
	}


	print_result(&l);

	//	print_possible_paths(&l);
	//	while (l.path)
	//	{
	//		printf("nombre de chemins differents : %d\n", l.path->different_path);
	//		l.path = l.path->next;
	//	}

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
