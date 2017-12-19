/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_remove_useless_paths.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:14:34 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:14:35 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	check_sum_end_start(t_lemin *l)
{
	if (l->sum[l->room_start] == 0)
	{
		free(l->sum);
		free_pipes(l, "\033[091mErreur : Salle de depart non reliee\033[0m");
	}
	if (l->sum[l->room_end] == 0)
	{
		free(l->sum);
		free_pipes(l, "\033[091mErreur : Salle de fin non reliee\033[0m");
	}
}

void		remove_useless_paths(t_lemin *l)
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
