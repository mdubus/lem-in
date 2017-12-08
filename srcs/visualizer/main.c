/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:00:49 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/08 11:42:36 by mdubus           ###   ########.fr       */
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

static void	draw_anthill(t_lemin *l, t_visu *v)
{
	t_room_visu	*room;

	room = v->begin;
	// Put all on the v.all texture
	v->all = SDL_CreateTexture(v->screen, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, WIDTH_W, HEIGHT_W);
	v->init_all = 1;
	SDL_SetRenderTarget(v->screen, v->all);
	SDL_RenderCopy(v->screen, v->background, NULL, NULL);
	SDL_SetRenderDrawColor(v->screen, 109, 90, 73, 255);
	draw_pipes(l, v);
	while (room)
	{
		draw_room(l, v, room);
		draw_room_name(l, v, room);
		room = room->next;
	}
	// stop stocking all on the texture
	SDL_SetRenderTarget(v->screen, NULL);
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
	v.nb_ant_start = l.nb_ants;
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

	print_turns(&l, &v);

	init_SDL(&l, &v);
	init_window(&l, &v);
	init_typo(&l, &v);
	init_background(&l, &v);
	init_ant(&l, &v);

	draw_anthill(&l, &v);


	SDL_RenderCopy(v.screen, v.all, NULL, NULL);

	if (v.nb_ant_start > 0)
	{
		v.coor = init_coor(v.startx, v.starty, v.width_room, v.height_room);
		SDL_RenderCopy(v.screen, v.ant_img, NULL, &v.coor);
	}
	if (v.nb_ant_end > 0)
	{
		v.coor = init_coor(v.startx, v.starty, v.width_room, v.height_room);
		SDL_RenderCopy(v.screen, v.ant_img, NULL, &v.coor);
	}
	SDL_RenderPresent(v.screen);

	room = v.begin;

	while (room)
	{
		printf("%d : %s\n", room->id, room->name);
		room = room->next;
	}


	//	SDL_RenderClear(render);
	//	SDL_RenderCopy(render, texture, NULL, NULL);
	//	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	//	SDL_RenderDrawLine(render, 100, 100, 150, 200);

	v.turn = v.turn_begin;

	event_loop(&v, &l);
	free_all_and_quit(&l, &v);

}
