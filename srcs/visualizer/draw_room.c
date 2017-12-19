/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 14:34:17 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 14:34:18 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

void		draw_room_name(t_lemin *l, t_visu *v, t_room_visu *room)
{
	SDL_Surface	*temp;

	temp = NULL;
	if (room->special != START && room->special != END)
	{
		if (TTF_SizeText(v->typo, room->name, &v->coor.w, &v->coor.h) == -1)
			free_all_msg(l, v, "Error on draw_room_name : ");
		v->coor.y = room->y + v->height_room + 5;
		v->coor.x = room->x + ((v->width_room - v->coor.w) / 2);
		if ((temp = TTF_RenderText_Blended(v->typo, room->name,
						v->white)) == NULL)
			free_all_msg(l, v, "Error on draw_room_name : ");
		if ((v->texture = SDL_CreateTextureFromSurface(v->screen,
						temp)) == NULL)
			free_all_msg(l, v, "Error on draw_room_name : ");
		if ((SDL_RenderCopy(v->screen, v->texture, NULL, &v->coor)) < 0)
			free_all_msg(l, v, "Error on draw_room_name : ");
		SDL_FreeSurface(temp);
		SDL_DestroyTexture(v->texture);
	}
}

static void	draw_fat_border_rectangle(t_lemin *l, t_visu *v, t_room_visu *room,
		int thickness)
{
	int	i;

	i = 0;
	if ((SDL_SetRenderDrawColor(v->screen, 164, 152, 141, 255)) < 0)
		free_all_msg(l, v, "Error on draw_room : ");
	while (i < thickness)
	{
		v->coor = init_coor(room->x - i, room->y - i, v->width_room + (i * 2),
				v->height_room + (i * 2));
		if ((SDL_RenderDrawRect(v->screen, &v->coor)) < 0)
			free_all_msg(l, v, "Error on draw_fat_border_rectangle : ");
		i++;
	}
	if ((SDL_SetRenderDrawColor(v->screen, 109, 90, 73, 255)) < 0)
		free_all_msg(l, v, "Error on draw_room : ");
}

void		draw_room(t_lemin *l, t_visu *v, t_room_visu *room)
{
	v->coor = init_coor(room->x, room->y, v->width_room, v->height_room);
	if (room->special == SNORLAX)
	{
		init_snorlax(l, v);
		if ((SDL_RenderCopy(v->screen, v->snorlax, NULL, &v->coor)) < 0)
			free_all_msg(l, v, "Error on draw_room : ");
	}
	else if (room->special == LAVA)
	{
		init_lava(l, v);
		if ((SDL_RenderCopy(v->screen, v->lava, NULL, &v->coor)) < 0)
			free_all_msg(l, v, "Error on draw_room : ");
	}
	else
		SDL_RenderFillRect(v->screen, &v->coor);
	if (room->special == START || room->special == END)
		draw_fat_border_rectangle(l, v, room, 3);
	if (room->special == START)
	{
		v->startx = room->x;
		v->starty = room->y;
	}
}
