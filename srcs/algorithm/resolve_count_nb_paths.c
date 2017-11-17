/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_count_nb_paths.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:12:51 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/17 18:03:51 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"

static void	create_path(t_lemin *l)
{
	if (!l->path)
	{
		l->path = (t_path*)malloc(sizeof(t_path));
		if (!l->path)
			free_pipes_and_sum(l, "\033[091mErreur d'allocation\033[0m");
		l->path_begin = l->path;
	}
	else
	{
		l->path->next = (t_path*)malloc(sizeof(t_path));
		if (!l->path->next)
			free_pipes_and_sum(l, "\033[091mErreur d'allocation\033[0m");
		l->path = l->path->next;
	}
}

static void	stock_path(t_lemin *l)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < l->nb_rooms && l->sorted[i] != l->room_end)
		i++;
	create_path(l);
	l->path->next = NULL;
	l->path->different_path = 0;
	l->path->nbr_coups = i;
	l->path->nbr_coups_min = 0;
	l->path->path = (int *)malloc(sizeof(int) * (unsigned long)(i + 1));
	if (!l->path->path)
		free_pipes_and_sum(l, "\033[091mErreur d'allocation\033[0m");
	i = 1;
	while (i < l->nb_rooms && l->sorted[i] != l->room_end)
		l->path->path[j++] = l->sorted[i++];
	l->path->path[j++] = l->room_end;
	l->path->path[j] = -1;
}

static void	room_end_found(t_lemin *l, int i, int *j, int room)
{
	l->sorted[*j] = i;
	stock_path(l);
	(l->nb_path)++;
	l->pipes[room][i] = 1;
	l->pipes[i][room] = 1;
	(*j)--;
	l->lookup[room] = -1;

}

static int	resolve_nb_paths(t_lemin *l, int room, int *j)
{
	int	i;

	i = -1;
	while (++i < l->nb_rooms)
	{
		if (l->pipes[room][i] == 1)
		{
			(*j)++;
			if (room != l->room_start)
				l->lookup[room] = (*j - 1);
			l->sorted[*j - 1] = room;
			l->pipes[room][i] = 0;
			l->pipes[i][room] = 0;
			if (i == l->room_end)
				room_end_found(l, i, j, room);
			else if (l->lookup[i] > 0 || i == l->room_start)
			{
				already_explored(l, j, room, i);
				l->sorted[*j] = -1;
			}
			else
			{
				resolve_nb_paths(l, i, j);
				back_in_stack(l, j, room, i);
				l->sorted[*j] = -1;
			}
		}
	}
	l->sorted[*j] = -1;
	return (0);
}

void		count_nb_paths(t_lemin *l)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	l->lookup = (int *)malloc(sizeof(int) * (unsigned long)(l->nb_rooms));
	if (!l->lookup)
		free_pipes_and_sum(l, "\033[091mErreur d'allocation\033[0m");
	while (i < l->nb_rooms)
		l->lookup[i++] = -1;
	i = 0;
	l->sorted = (int *)malloc(sizeof(int) * (unsigned long)(l->nb_rooms));
	if (!l->sorted)
		free_pipes_and_sum(l, "\033[091mErreur d'allocation\033[0m");
	while (i < l->nb_rooms)
		l->sorted[i++] = -1;
	resolve_nb_paths(l, l->room_start, &j);
	if (l->nb_path == 0)
		free_pipes_and_sum(l, "\033[091mAucun chemin possible\033[0m");
	free(l->lookup);
}
