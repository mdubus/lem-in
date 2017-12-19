/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:20:08 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:20:09 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	put_new_coor_ant(t_visu *v, int i)
{
	t_room_visu	*room;
	int			j;

	v->ant = v->ant_begin;
	j = i;
	if (v->turn->turn[i] == v->end_room_id)
	{
		v->ant_end++;
	}
	while (j > 1 && v->ant->next)
	{
		v->ant = v->ant->next;
		j--;
	}
	room = v->begin;
	while (room && room->id != v->turn->turn[i])
		room = room->next;
	v->ant->nextx = room->x;
	v->ant->nexty = room->y;
}

void		move_ant(t_lemin *l, t_visu *v)
{
	int	i;

	i = 0;
	while (i <= l->nb_ants)
	{
		if (v->turn->turn[i] != -1)
			put_new_coor_ant(v, i);
		i++;
	}
	v->ant = v->ant_begin;
	while (v->ant)
	{
		if ((v->ant->nextx != -1 && v->ant->prevx == -1) ||
				(v->ant->nexty != -1 && v->ant->prevy == -1))
		{
			v->nb_ant_start--;
			v->ant->prevx = v->begin_roomx;
			v->ant->prevy = v->begin_roomy;
		}
		v->ant = v->ant->next;
	}
	move(l, v);
	v->turn = v->turn->next;
}
