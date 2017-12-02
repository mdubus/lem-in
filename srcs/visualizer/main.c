/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:00:49 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/29 18:36:09 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

void	put_on_screen_sdl(t_visu *v, SDL_Surface *surface, int x, int y)
{
	SDL_Rect	coor;

	coor.x = x;
	coor.y = y;
if (SDL_BlitSurface(surface, NULL, v->surf, &coor) < 0)
{
	ft_putstr("Error put_on_screen_sdl : ");
	SDL_GetError();
}
}

void	put_all_on_screen_sdl(t_visu *v, SDL_Surface *surface)
{
	SDL_Rect	coor;

	coor.x = 0;
	coor.y = 0;
	coor.w = v->width_w;
	coor.h = v->height_w;
	if (SDL_BlitSurface(surface, &coor, v->surf, NULL) < 0)
	{
		ft_putstr("Error put_all_on_screen_sdl : ");
		SDL_GetError();
	}
}

static void	refresh_background(t_visu *v, SDL_Surface *surface, int x, int y)
{
	SDL_Rect	coor;

	coor.x = x;
	coor.y = y;
	coor.w = v->ant->w;
	coor.h = v->ant->h;
	if (SDL_BlitSurface(surface, &coor, v->surf, &coor) < 0)
	{
		ft_putstr("Error on BlitSurface : ");
		SDL_GetError();
	}
}

void	move_ant(t_visu *v)
{
	v->temps_actuel = SDL_GetTicks();
	if (v->temps_actuel - v->temps_precedent > SKIP_TICKS)
	{
		refresh_background(v, v->background, v->x, v->y);
		v->x += v->ant_speed;
		v->y += v->ant_speed;
		put_on_screen_sdl(v, v->ant, v->x, v->y);
		v->temps_precedent = v->temps_actuel;
		SDL_UpdateWindowSurface(v->window);
	}
}

static void	check_start_end(t_lemin *l)
{
	if (l->room_end == -1)
		free_check_if_room(l,
			"\033[091mErreur : Aucune salle de fin\033[0m]]");
	if (l->room_start == -1)
		free_check_if_room(l,
			"\033[091mErreur : Aucune salle de depart\033[0m]]");
	if (l->nb_rooms == 0)
		free_check_if_room(l,
			"\033[091mErreur : Aucune room\033[0m]]");
	if (l->room_start == l->room_end)
		free_check_if_room(l,
			"\033[091mErreur : Start et end identiques\033[0m]]");
}

static void	draw_rect(t_visu *v, SDL_Rect *rect)
{
	SDL_Surface	*surface;

	surface = SDL_CreateRGBSurface(0, rect->w, rect->h, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(v->surf->format, 109, 90, 73));
	SDL_BlitSurface(surface, NULL, v->surf, rect);
	SDL_UpdateWindowSurface(v->window);
}

static void	draw_room(t_visu *v, int x, int y)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = v->ant->w + 10;
	rect.h = 5;
	draw_rect(v, &rect);

	rect.w = 5;
	rect.h = v->ant->h + 10;
	draw_rect(v, &rect);

	rect.y = y + v->ant->h + 10;
	rect.w = v->ant->w + 10;
	rect.h = 5;
	draw_rect(v, &rect);

	rect.x = x + v->ant->w + 10;
	rect.y = y;
	rect.w = 5;
	rect.h = v->ant->h + 10 + 5;
	draw_rect(v, &rect);
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
		free_check_if_room(&l,
				"\033[091mErreur : La map est mal formatee\033[0m");
	if (l.nb_rooms > 15)
		free_check_if_room(&l,
			"\033[091mErreur : Trop de rooms pour le visualisateur\033[0m]]");
	visu_parsing_pipes(&l, &v);
	check_start_end(&l);
	stock_turns(&l, &v);
	ft_putendl(l.string_file);

//	print_rooms(&v);
//	print_turns(&l, &v);


	init_SDL(&v);
	init_window_and_surface(&v);


	put_all_on_screen_sdl(&v, v.background);
	put_on_screen_sdl(&v, v.ant, 210, 160);

	draw_room(&v, 200, 150);


//	SDL_Surface	*temp;
	
//	temp = TTF_RenderText_Blended(v.typo, "start", v.white);
//	put_on_screen_sdl(&v, temp, 200, 200);


	SDL_UpdateWindowSurface(v.window);


	event_loop(&v, &l);
	free_all_and_quit(&l, &v);

}
