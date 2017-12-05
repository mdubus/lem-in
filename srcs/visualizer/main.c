/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:00:49 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/04 18:00:23 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	check_start_end(t_lemin *l)
{
	if (l->room_end == -1)
		free_check_if_room(l, "\033[091mErreur : Aucune salle de fin\033[0m]]");
	if (l->room_start == -1)
		free_check_if_room(l,
				"\033[091mErreur : Aucune salle de depart\033[0m]]");
	if (l->nb_rooms == 0)
		free_check_if_room(l, "\033[091mErreur : Aucune room\033[0m]]");
	if (l->room_start == l->room_end)
		free_check_if_room(l,
				"\033[091mErreur : Start et end identiques\033[0m]]");
}

SDL_Rect	init_coor(int x, int y, int w, int h)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

static void	draw_room_name(t_lemin *l, t_visu *v, t_room_visu *room)
{
	SDL_Surface	*temp;
	SDL_Rect	coor;
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
	coor = init_coor(textx, texty, w, h);

	v->texture = SDL_CreateTextureFromSurface(v->screen, temp);
	SDL_RenderCopy(v->screen, v->texture, NULL, &coor);

	SDL_FreeSurface(temp);
	SDL_DestroyTexture(v->texture);
}

static void	draw_room(t_visu *v, t_room_visu *room, SDL_Rect *pos)
{
	if (room->special == 0 || room->special == START || room->special == END)
	{
		*pos = init_coor(room->x, room->y, v->width_room, v->height_room);
		SDL_RenderFillRect(v->screen, pos);
	}
	if (room->special == START)
	{
		SDL_SetRenderDrawColor(v->screen, 255, 0, 0, 255);
		SDL_RenderDrawRect(v->screen, pos);
		SDL_SetRenderDrawColor(v->screen, 109, 90, 73, 255);
	}
	else if (room->special == END)
	{
		SDL_SetRenderDrawColor(v->screen, 0, 255, 0, 255);
		SDL_RenderDrawRect(v->screen, pos);
		SDL_SetRenderDrawColor(v->screen, 109, 90, 73, 255);
	}
}

static void	draw_anthill(t_lemin *l, t_visu *v)
{
	SDL_Rect	pos;
	t_room_visu	*room;

	room = v->begin;
	SDL_RenderCopy(v->screen, v->background, NULL, NULL);
	SDL_SetRenderDrawColor(v->screen, 109, 90, 73, 255);
	while (room)
	{
		draw_room(v, room, &pos);
		draw_room_name(l, v, room);
		room = room->next;
	}
	pos = init_coor(100, 50, v->width_room, v->height_room);
	SDL_RenderCopy(v->screen, v->ant, NULL, &pos);

	SDL_RenderPresent(v->screen);
}


int	main(void)
{
	t_visu		v;
	t_lemin		l;
	t_room_visu	*room;

	init_struct_lemin(&l);
	init_struct(&v);
	get_file(&l);
	parsing_ants_number(&l);
	if (visu_parsing_room_and_stock(&l, &room, &v) == 2)
		free_room_visu(&l,
				"\033[091mErreur : La map est mal formatee\033[0m", &v);
	if (l.nb_rooms > 15)
		free_room_visu(&l,
				"\033[091mErreur : Trop de rooms pour le visualisateur\033[0m]]", &v);
	visu_parsing_pipes(&l, &v);
	check_start_end(&l);
	stock_turns(&l, &v);
	ft_putendl(l.string_file);


	init_SDL(&l, &v);
	init_window(&l, &v);
	init_typo(&l, &v);
	init_background(&l, &v);
	init_ant(&l, &v);

	draw_anthill(&l, &v);




	//	SDL_RenderClear(render);
	//	SDL_RenderCopy(render, texture, NULL, NULL);
	//	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	//	SDL_RenderDrawLine(render, 100, 100, 150, 200);

	event_loop(&v, &l);
	free_all_and_quit(&l, &v);

}
