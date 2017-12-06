/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:34:38 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/06 15:41:18 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	get_end_start_room(t_lemin *l, t_visu *v, int i, int j)
{
	t_room_visu	*room;

	room = v->begin;
	while (room && room->id != i)
		room = room->next;
	v->startx = room->x;
	v->starty = room->y;
	room = v->begin;
	while (room && room->id != j)
		room = room->next;
	v->endx = room->x;
	v->endy = room->y;
	l->pipes[i][j] = 0;
	l->pipes[j][i] = 0;
}

static void	draw_relations(t_visu *v, int midx, int midy)
{
	SDL_SetRenderDrawColor(v->screen, 99, 80, 63, 255);
	SDL_RenderDrawLine(v->screen, v->startx + midx, v->starty + midy,
			v->endx + midx, v->endy + midy);
	SDL_RenderDrawLine(v->screen, v->startx + midx + 1, v->starty + midy,
			v->endx + midx + 1, v->endy + midy);
	SDL_RenderDrawLine(v->screen, v->startx + midx, v->starty + midy + 1,
			v->endx + midx, v->endy + midy + 1);
	SDL_RenderDrawLine(v->screen, v->startx + midx - 1, v->starty + midy,
			v->endx + midx - 1, v->endy + midy);
	SDL_RenderDrawLine(v->screen, v->startx + midx, v->starty + midy - 1,
			v->endx + midx, v->endy + midy - 1);
	SDL_SetRenderDrawColor(v->screen, 109, 90, 73, 255);
}

void	draw_pipes(t_lemin *l, t_visu *v)
{
	int			i;
	int			j;
	int			midx;
	int			midy;

	i = 0;
	midx = v->width_room / 2;
	midy = v->height_room / 2;
	while (i < l->nb_rooms)
	{
		j = 0;
		while (j < l->nb_rooms)
		{
			if (l->pipes[i][j] == 1)
			{
				get_end_start_room(l, v, i, j);
				draw_relations(v, midx, midy);
			}
			j++;
		}
		i++;
	}
}