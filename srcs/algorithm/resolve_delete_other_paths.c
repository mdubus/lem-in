/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_delete_other_paths.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:58:16 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/17 17:33:53 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"

static void	delete_path(t_lemin *l, int *flag, t_path *prev)
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
	*flag = 0;
}

static void	search_identical_rooms(t_lemin *l, int *flag)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (l->best_path->path[i] != l->room_end && *flag == 0)
	{
		j = 0;
		while (l->path->path[j] != l->room_end && *flag == 0)
		{
			if (l->best_path->path[i] == l->path->path[j])
				*flag = 1;
			j++;
		}
		i++;
	}
}

void		delete_other_paths(t_lemin *l)
{
	t_path	*prev;
	int		flag;

	flag = 0;
	l->path = l->path_begin;
	prev = l->path_begin;
	while (l->path)
	{
		if (l->path != l->best_path)
			search_identical_rooms(l, &flag);
		if (flag == 1)
			delete_path(l, &flag, prev);
		else
		{
			prev = l->path;
			l->path = l->path->next;
		}
	}
}
