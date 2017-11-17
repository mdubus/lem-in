/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_remove_useless_paths.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 17:13:44 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/17 11:05:03 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"

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

void	remove_useless_paths(t_lemin *l)
{
	create_sum_tab(l);
	update_sum_tab(l);
	check_sum_end_start(l);
	if (l->graph == 1)
		export_graph(l->pipes, l);
	check_if_solution_exists(l);
	bfs(l, l->room_start);
	bfs(l, l->room_end);
	update_sum_tab(l);
	check_for_isolated_rooms(l);
	count_nb_paths(l);
}
