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

void	init_background(t_lemin *l, t_visu *v)
{
	SDL_Surface		*background;

	background = IMG_Load("srcs/visualizer/img/background.png");
	if (!background)
	{
		ft_putstr("Unable to initialize background : ");
		ft_putendl(SDL_GetError());
		free_all_and_quit(l, v);
	}
	if ((v->background = SDL_CreateTextureFromSurface(v->screen, background)) == NULL)
	{
		ft_putstr("Unable to create background texture : ");
		ft_putendl(SDL_GetError());
		free_all_and_quit(l, v);
	}
	else
		v->init_background = 1;
	SDL_FreeSurface(background);
}

static void	init_ant(t_lemin *l, t_visu *v)
{
	SDL_Surface		*ant;

	ant = IMG_Load("srcs/visualizer/img/ant2.png");
	if (!ant)
	{
		ft_putstr("Unable to initialize ant : ");
		ft_putendl(SDL_GetError());
		free_all_and_quit(l, v);
	}
	v->width_room = ant->w;
	v->height_room = ant->h;
	if ((v->ant = SDL_CreateTextureFromSurface(v->screen, ant)) == NULL)
	{
		ft_putstr("Unable to create ant texture : ");
		ft_putendl(SDL_GetError());
		free_all_and_quit(l, v);
	}
	else
		v->init_ant = 1;
	SDL_FreeSurface(ant);
}

static void	draw_anthill(t_visu *v)
{
	SDL_Rect	pos;

	pos.x = 150;
	pos.y = 100;
	pos.w = v->width_room;
	pos.h = v->height_room;
	SDL_RenderCopy(v->screen, v->background, NULL, NULL);
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

	draw_anthill(&v);




	//	SDL_RenderClear(render);
	//	SDL_RenderCopy(render, texture, NULL, NULL);
	//	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	//	SDL_RenderDrawLine(render, 100, 100, 150, 200);

	event_loop(&v, &l);
	free_all_and_quit(&l, &v);

}
