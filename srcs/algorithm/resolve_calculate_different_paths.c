/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_calculate_different_paths.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:06:32 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/14 16:12:34 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	get_coups_min(t_lemin *l, t_path **next)
{
	int	nbr_coups_min;

	nbr_coups_min = 0;
	l->path->different_path += 1;
	nbr_coups_min = l->path->nbr_coups + (*next)->nbr_coups;
	if (l->path->nbr_coups_min == 0 || l->path->nbr_coups_min < nbr_coups_min)
		l->path->nbr_coups_min = nbr_coups_min;
}

static void	find_different_paths(t_lemin *l, t_path **next)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	*next = (*next)->next;
	i = 0;
	while (l->path->path[i] != l->room_end && flag == 0)
	{
		j = 0;
		while ((*next)->path[j] != l->room_end && flag == 0)
		{
			if (l->path->path[i] == (*next)->path[j])
				flag = 1;
			j++;
		}
		i++;
	}
	if (flag == 0)
		get_coups_min(l, next);
	flag = 0;
}

void		calculate_different_paths(t_lemin *l)
{
	t_path	*next;

	next = NULL;
	l->path = l->path_begin;
	next = l->path;
	while (l->path)
	{
		while (next->next)
			find_different_paths(l, &next);
		l->path = l->path->next;
		next = l->path;
	}
}
