/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:20:08 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/28 13:08:48 by mdubus           ###   ########.fr       */
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
		v->ant_end++;
	while (j-- > 1 && v->ant->next)
		v->ant = v->ant->next;
	room = v->begin;
	while (room && room->id != v->turn->turn[i])
		room = room->next;
	v->ant->nextx = room->x;
	v->ant->nexty = room->y;
	v->ant->beginx = v->ant->prevx;
	v->ant->beginy = v->ant->prevy;
	v->ant->modx = 0;
	v->ant->mody = 0;
}

static void	ants_from_start(t_visu *v)
{
	if ((v->ant->nextx != -1 && v->ant->prevx == -1) ||
			(v->ant->nexty != -1 && v->ant->prevy == -1))
	{
		v->nb_ant_start--;
		v->ant->prevx = v->begin_roomx;
		v->ant->prevy = v->begin_roomy;
		v->ant->beginx = v->begin_roomx;
		v->ant->beginy = v->begin_roomy;
	}
}

static void	calc_mod(t_visu *v, bool xy, bool negpos)
{
	double	temp;

	temp = 0.0;
	if (xy == X)
	{
		v->ant->modx = (negpos == POS) ? v->ant_speed : -v->ant_speed;
		if (v->diffy != 0)
		{
			temp = (v->diffy * v->ant_speed) / v->diffx;
			v->ant->mody = (negpos == POS) ? temp : -temp;
		}
	}
	else if (xy == Y)
	{
		v->ant->mody = (negpos == POS) ? v->ant_speed : -v->ant_speed;
		if (v->diffx != 0)
		{
			temp = (v->diffx * v->ant_speed) / v->diffy;
			v->ant->modx = (negpos == POS) ? temp : -temp;
		}
	}
}

static void	ant_is_moving(t_visu *v)
{
	v->diffx = v->ant->nextx - v->ant->beginx;
	v->diffy = v->ant->nexty - v->ant->beginy;
	if (v->diffx > 0)
		calc_mod(v, X, POS);
	else if (v->diffx < 0)
		calc_mod(v, X, NEG);
	else if (v->diffy > 0)
		calc_mod(v, Y, POS);
	else if (v->diffy < 0)
		calc_mod(v, Y, NEG);
}

void		move_ant(t_lemin *l, t_visu *v)
{
	int		i;

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
		ants_from_start(v);
		if (v->ant->nextx != v->ant->prevx || v->ant->nexty != v->ant->prevy)
			ant_is_moving(v);
		v->ant = v->ant->next;
	}
	move(l, v);
	v->turn = v->turn->next;
}
