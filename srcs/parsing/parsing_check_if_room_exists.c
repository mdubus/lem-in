/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_if_room_exists.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 13:14:44 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/28 13:34:07 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	get_room_id(t_lemin *l, char **tab, bool *special1, bool *special2)
{
	l->room = l->begin;
	l->froom1 = -1;
	l->froom2 = -1;
	while (l->room)
	{
		if (ft_strcmp(l->room->name, tab[0]) == 0)
		{
			l->froom1 = l->room->id;
			if (l->room->special != -1)
				*special1 = 1;
		}
		if (ft_strcmp(l->room->name, tab[1]) == 0)
		{
			l->froom2 = l->room->id;
			if (l->room->special != -1)
				*special2 = 1;
		}
		l->room = l->room->next;
	}
}

void		check_if_rooms_exists(t_lemin *l, char **tab)
{
	bool	special1;
	bool	special2;

	special1 = 0;
	special2 = 0;
	get_room_id(l, tab, &special1, &special2);
	l->room = l->begin;
	if (l->froom1 == -1 || l->froom2 == -1)
	{
		ft_free_double_tab((void**)tab);
		free_pipes(l,
			"\033[091mErreur : Tubes lies a des salles inconnues\033[0m");
	}
	if (special1 == 0 && special2 == 0)
	{
		l->pipes[l->froom2][l->froom1] = 1;
		l->pipes[l->froom1][l->froom2] = 1;
	}
}
