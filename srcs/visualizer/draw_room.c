/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:42:34 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/06 15:44:30 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

void	draw_room_name(t_lemin *l, t_visu *v, t_room_visu *room)
{
	SDL_Surface	*temp;
	int			w;
	int			h;
	int			textx;
	int			texty;

	w = 0;
	h = 0;
	texty = 0;
	textx = 0;
	if (TTF_SizeText(v->typo, room->name, &w, &h) == -1)
	{
		ft_putendl("Error on draw_room");
		free_all_and_quit(l, v);
	}
	texty = room->y + v->height_room + 5;
	textx = room->x + ((v->width_room - w) / 2);
	temp = TTF_RenderText_Blended(v->typo, room->name, v->white);
	v->coor = init_coor(textx, texty, w, h);
	v->texture = SDL_CreateTextureFromSurface(v->screen, temp);
	SDL_RenderCopy(v->screen, v->texture, NULL, &v->coor);
	SDL_FreeSurface(temp);
	SDL_DestroyTexture(v->texture);
}

static void	draw_fat_border_rectangle(t_visu *v, t_room_visu *room,
		int thickness)
{
	int	i;

	i = 0;
	while (i < thickness)
	{
		v->coor = init_coor(room->x - i, room->y - i, v->width_room + (i * 2),
				v->height_room + (i * 2));
		SDL_RenderDrawRect(v->screen, &v->coor);
		i++;
	}
}

void	draw_room(t_lemin *l, t_visu *v, t_room_visu *room)
{
	v->coor = init_coor(room->x, room->y, v->width_room, v->height_room);
	if (room->special == SNORLAX)
	{
		init_snorlax(l, v);
		SDL_RenderCopy(v->screen, v->snorlax, NULL, &v->coor);
	}
	else if (room->special == LAVA)
	{
		init_lava(l, v);
		SDL_RenderCopy(v->screen, v->lava, NULL, &v->coor);
	}
	else
		SDL_RenderFillRect(v->screen, &v->coor);
	if (room->special == START || room->special == END)
	{
		SDL_SetRenderDrawColor(v->screen, 164, 152, 141, 255);
		draw_fat_border_rectangle(v, room, 3);
		SDL_SetRenderDrawColor(v->screen, 109, 90, 73, 255);
	}
	if (room->special ==  START)
	{
		v->startx = room->x;
		v->starty = room->y;
	}
}
