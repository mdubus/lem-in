/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_get_ants.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:48:28 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/22 15:53:15 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"

static void	print_ants(t_lemin *l)
{
	int		i;
	t_room	*path;

	i = 0;
	path = NULL;
	while (l->result[i] != NULL)
	{
		path = l->result[i];
		while (path && path->id != l->room_start && l->ant_finish < l->nb_ants)
		{
			if (path->ant > 0)
			{
				if (path->id == l->room_end)
					l->ant_finish++;
				ft_printf("L%d-%s ", path->ant, l->eq[path->id]);
			}
			path = path->next;
		}
		i++;
	}
	ft_putchar('\n');
}

static void	get_next_ant(t_lemin *l, t_room **path, int *ant)
{
	if ((*path)->next && (*path)->next->id == l->room_start &&
			*ant <= l->nb_ants)
	{
		(*path)->ant = *ant;
		(*ant)++;
	}
	else if ((*path)->next && (*path)->next->ant > 0 &&
			(*path)->next->id != l->room_start)
	{
		(*path)->ant = (*path)->next->ant;
		(*path)->next->ant = 0;
	}
	*path = (*path)->next;
}

void		get_ants(t_lemin *l)
{
	int		ant;
	int		i;
	t_room	*path;

	ant = 1;
	i = 0;
	path = NULL;
	while (l->ant_finish < l->nb_ants)
	{
		while (l->result[i] != NULL)
		{
			path = l->result[i];
			while (path && path->id != l->room_start)
			{
				get_next_ant(l, &path, &ant);
			}
			i++;
		}
		i = 0;
		print_ants(l);
	}
}
