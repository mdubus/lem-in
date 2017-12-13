/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_get_ants.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:48:28 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/13 18:14:50 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"

// Ajout de l->prev_length pour check la longueur du chemin precedent

static void	ants_vacuum(t_lemin *l, t_room *path, int *ant_nb)
{
	int	rest;

	rest = l->nb_ants - *ant_nb + 1;
	if (path->next->id == l->room_start && *ant_nb <= l->nb_ants)
	{
		path->ant = *ant_nb;
		ft_printf("L%d-%s ", path->ant, l->eq[path->id]);
		(*ant_nb)++;
	}
	else if (path->next->ant > 0 && path->id != l->room_end &&
			path->next->id != l->room_start)
	{
		path->ant = path->next->ant;
		path->next->ant = -1;
		ft_printf("L%d-%s ", path->ant, l->eq[path->id]);
	}
	else if (path->next->ant > 0 && path->id == l->room_end &&
			l->ant_finish < l->nb_ants)
	{
		path->ant = path->next->ant;
		path->next->ant = -1;
		ft_printf("L%d-%s ", path->ant, l->eq[path->id]);
		l->ant_finish++;
	}
	l->prev_length = path->length;
}

void		get_ants(t_lemin *l)
{
	int		ant_nb;
	int		i;
	t_room	*path;

	ant_nb = 1;
	path = NULL;
	l->ant_finish = 0;
	while (l->ant_finish < l->nb_ants) // A chaque tour
	{
		i = 0;
		while (l->result[i]) // Pour chaque chemin possible
		{
			path = l->result[i];
			while (path->next)	// On parcours chaque room
			{
				ants_vacuum(l, path, &ant_nb);
				path = path->next;
			}
			i++;
		}
		ft_putchar('\n');
	}
}
