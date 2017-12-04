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
	else
		v->init_background = 1;
	if ((v->background = SDL_CreateTextureFromSurface(v->screen, background)) == NULL)
	{
		ft_putstr("Unable to create background texture : ");
		ft_putendl(SDL_GetError());
		free_all_and_quit(l, v);
	}
	SDL_FreeSurface(background);
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


	SDL_RenderCopy(v.screen, v.background, NULL, NULL);
	SDL_RenderPresent(v.screen);


/*
	SDL_Surface		*ant;

	SDL_RenderCopy(v.screen, v.background, NULL, NULL);
	
	SDL_Rect	rect;

	ant = IMG_Load("srcs/visualizer/img/ant2.png");
	rect.w = ant->w;
	rect.h = ant->h;
	v.ant = SDL_CreateTextureFromSurface(v.screen, ant);
	SDL_QueryTexture(v.ant, NULL, NULL, &v.width_room, &v.height_room);
	SDL_RenderCopy(v.screen, v.ant, &rect, &rect);
	
	

	printf("w = %d, h = %d\n", v.width_room, v.height_room);





//	SDL_RenderClear(render);
//	SDL_RenderCopy(render, texture, NULL, NULL);
//	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
//	SDL_RenderDrawLine(render, 100, 100, 150, 200);
	SDL_RenderPresent(v.screen);

//	init_window_and_surface(&v);
	init_background(&l, &v);



	put_all_on_screen_sdl(&v, v.background);
	put_on_screen_sdl(&v, v.ant, v.begin->x + 10, v.begin->y + 10);
	SDL_UpdateWindowSurface(v.window);
*/

	event_loop(&v, &l);
	free_all_and_quit(&l, &v);

}
