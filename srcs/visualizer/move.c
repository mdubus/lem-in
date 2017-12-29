/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:20:02 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/28 13:18:53 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	draw_ant_nb(t_lemin *l, t_visu *v, int flag)
{
	if (v->nb_ant_start > 0)
	{
		v->coor = init_coor(v->begin_roomx, v->begin_roomy, v->width_room,
				v->height_room);
		if ((SDL_RenderCopy(v->screen, v->ant_img, NULL, &v->coor)) < 0)
			free_all_msg(l, v, "Error in draw_ant_nb : ");
	}
	if (v->nb_ant_end > 0)
	{
		v->coor = init_coor(v->end_roomx, v->end_roomy, v->width_room,
				v->height_room);
		if ((SDL_RenderCopy(v->screen, v->ant_img, NULL, &v->coor)) < 0)
			free_all_msg(l, v, "Error in draw_ant_nb : ");
	}
	if (!v->ant && flag == 1)
	{
		v->nb_ant_end += v->ant_end;
		v->ant_end = 0;
	}
	draw_start_end_name(l, v);
}

static void	put_prev_coor1(t_visu *v, bool *flag)
{
	if (v->ant->prevx > v->ant->nextx)
	{
		v->ant->prevx += v->ant->modx;
		if (v->ant->prevx < v->ant->nextx)
			v->ant->prevx = v->ant->nextx;
		*flag = 0;
	}
	else if (v->ant->prevx < v->ant->nextx)
	{
		v->ant->prevx += v->ant->modx;
		if (v->ant->prevx > v->ant->nextx)
			v->ant->prevx = v->ant->nextx;
		*flag = 0;
	}
}

static void	put_prev_coor2(t_visu *v, bool *flag)
{
	if (v->ant->prevy > v->ant->nexty)
	{
		v->ant->prevy += v->ant->mody;
		if (v->ant->prevy < v->ant->nexty)
			v->ant->prevy = v->ant->nexty;
		*flag = 0;
	}
	else if (v->ant->prevy < v->ant->nexty)
	{
		v->ant->prevy += v->ant->mody;
		if (v->ant->prevy > v->ant->nexty)
			v->ant->prevy = v->ant->nexty;
		*flag = 0;
	}
}

static void	draw_ant(t_lemin *l, t_visu *v, bool *flag)
{
	put_prev_coor1(v, flag);
	put_prev_coor2(v, flag);
	if (v->ant->prevx != -1 && v->ant->prevy != -1 &&
			v->ant->nextx != -1 && v->ant->nexty != -1)
	{
		v->coor = init_coor(v->ant->prevx, v->ant->prevy, v->width_room,
				v->height_room);
		if ((SDL_RenderCopy(v->screen, v->ant_img, NULL, &v->coor)) < 0)
			free_all_msg(l, v, "Error in move : ");
	}
	v->ant = v->ant->next;
}

void		move(t_lemin *l, t_visu *v)
{
	bool	flag;

	flag = 0;
	while (flag == 0)
	{
		flag = 1;
		v->ant = v->ant_begin;
		if ((SDL_RenderClear(v->screen)) < 0)
			free_all_msg(l, v, "Error in move : ");
		if ((SDL_RenderCopy(v->screen, v->all, NULL, NULL)) < 0)
			free_all_msg(l, v, "Error in move : ");
		while (v->ant)
			draw_ant(l, v, &flag);
		draw_ant_nb(l, v, flag);
		SDL_RenderPresent(v->screen);
	}
}
