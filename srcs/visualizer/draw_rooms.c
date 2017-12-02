/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 11:19:22 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/29 16:52:11 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	draw_rect(t_lemin *l, t_visu *v, SDL_Rect *rect)
{
	SDL_Surface	*surface;

	if ((surface = SDL_CreateRGBSurface(0, rect->w,
		rect->h, 32, 0, 0, 0, 0)) == NULL)
	{
		ft_putendl("Error in draw_rect");
		free_all_and_quit(l, v);
	}
	if (SDL_FillRect(surface, NULL,
		SDL_MapRGB(v->surf->format, 109, 90, 73)) < 0)
	{
		SDL_FreeSurface(surface);
		ft_putendl("Error on draw_rect");
		free_all_and_quit(l, v);
	}
	if (SDL_BlitSurface(surface, NULL, v->surf, rect) < 0)
	{
		SDL_FreeSurface(surface);
		ft_putendl("Error on draw_rect");
		free_all_and_quit(l, v);
	}
}

static void	draw_room_name(t_lemin *l, t_visu *v, t_room_visu *room)
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
	put_on_screen_sdl(v, temp, textx, texty);
	SDL_FreeSurface(temp);
}

void	draw_room(t_lemin *l, t_visu *v, t_room_visu *room)
{
	SDL_Rect	rect;

	rect.x = room->x;
	rect.y = room->y;
	rect.w = v->width_room;
	rect.h = 5;
	draw_rect(l, v, &rect);
	rect.w = 5;
	rect.h = v->height_room;
	draw_rect(l, v, &rect);
	rect.y = room->y + v->height_room;
	rect.w = v->width_room;
	rect.h = 5;
	draw_rect(l, v, &rect);
	rect.x = room->x + v->width_room;
	rect.y = room->y;
	rect.w = 5;
	rect.h = v->height_room + 5;
	draw_rect(l, v, &rect);
	draw_room_name(l, v, room);
}
