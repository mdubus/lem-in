/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_count_nb_paths.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:12:51 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/16 11:03:01 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"
/*
static void	print_possible_paths(t_lemin *l)
{
	int j = 0;
	while (j < l->nb_rooms)
	{
		ft_putnbr(l->sorted[j++]);
		ft_putchar(' ');
	}
}
*/
static void	stock_path(t_lemin *l)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < l->nb_rooms && l->sorted[i] != l->room_end)
		i++;
	if (!l->path)
	{
		l->path = (t_path*)malloc(sizeof(t_path));
		l->path_begin = l->path;
	}
	else
	{
		l->path->next = (t_path*)malloc(sizeof(t_path));
		l->path = l->path->next;
	}
	l->path->next = NULL;
	l->path->different_path = 0;
	l->path->nbr_coups = i;
	l->path->nbr_coups_min = 0;
	l->path->path = (int *)malloc(sizeof(int) * (unsigned long)(i + 1));
	i = 1;
	while (i < l->nb_rooms && l->sorted[i] != l->room_end)
		l->path->path[j++] = l->sorted[i++];
	l->path->path[j++] = l->room_end;
	l->path->path[j] = -1;
}

static int	resolve_nb_paths(t_lemin *l, int room, int *j)
{
	int	i;

	i = 0;
	while (i < l->nb_rooms)
	{
		if (l->pipes[room][i] == 1)
		{
			(*j)++;
			if (room != l->room_start)
			{
				l->lookup[room] = (*j - 1);
			}
				l->sorted[*j - 1] = room;
			l->pipes[room][i] = 0;
			l->pipes[i][room] = 0;
			if (i == l->room_end)
			{
				l->sorted[*j] = i;
				stock_path(l);
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
				l->sorted[*j] = -1;
				l->pipes[room][i] = 1;
				l->pipes[i][room] = 1;
			}
			else
			{
				resolve_nb_paths(l, i, j);
				l->pipes[room][i] = 1;
				l->pipes[i][room] = 1;
				(*j)--;
				l->lookup[room] = -1;
				l->sorted[*j] = -1;
			}
		}
		i++;
	}
	l->sorted[*j] = -1;
	return (0);
}

void	count_nb_paths(t_lemin *l)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	l->lookup = (int *)malloc(sizeof(int) * (unsigned long)(l->nb_rooms));
	while (i < l->nb_rooms)
		l->lookup[i++] = -1;
	i = 0;
	l->sorted = (int *)malloc(sizeof(int) * (unsigned long)(l->nb_rooms));
	while (i < l->nb_rooms)
		l->sorted[i++] = -1;
	resolve_nb_paths(l, l->room_start, &j);
	if (l->nb_path == 0)
	{
		free(l->sum);
		ft_memdel((void**)&l->string_file);
		ft_free_double_tab((void**)l->file);
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		free_lst_name(l);
		error_lem_in(&ft_putendl_fd,
				"\033[091mAucun chemin possible\033[0m",
				STDERR_FILENO, l);
	}
	free(l->lookup);
}
