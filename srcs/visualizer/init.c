/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:19:34 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:19:35 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	init_struct3(t_visu *v)
{
	v->init_snorlax = 0;
	v->init_lava = 0;
	v->init_all = 0;
	v->loop_moving = 0;
	v->ants_stocked = 0;
	v->diffx = 0.0;
	v->diffy = 0.0;
}

static void	init_struct2(t_visu *v)
{
	v->startx = 0;
	v->starty = 0;
	v->endx = 0;
	v->endy = 0;
	v->begin_roomx = 0;
	v->begin_roomy = 0;
	v->end_roomx = 0;
	v->end_roomy = 0;
	v->end_room_id = 0;
	v->ant_speed = 1;
	v->nb_ant_start = 0;
	v->nb_ant_end = 0;
	v->ant_end = 0;
	v->loop = true;
	v->flag_move_right = 0;
	v->flag_move_left = 0;
	v->init_sdl = 0;
	v->init_img = 0;
	v->init_ttf = 0;
	v->init_window = 0;
	v->init_screen = 0;
	v->init_typo = 0;
	v->init_background = 0;
	v->init_ant = 0;
	init_struct3(v);
}

void		init_struct(t_visu *v)
{
	v->window = NULL;
	v->screen = NULL;
	v->background = NULL;
	v->ant_img = NULL;
	v->texture = NULL;
	v->snorlax = NULL;
	v->lava = NULL;
	v->surf = NULL;
	v->all = NULL;
	v->typo = NULL;
	v->white = init_color(255, 255, 255, 255);
	v->begin = NULL;
	v->first = NULL;
	v->next = NULL;
	v->turn_begin = NULL;
	v->turn = NULL;
	v->ant = NULL;
	v->ant_begin = NULL;
	v->string_file = NULL;
	v->file = NULL;
	v->width_room = 0;
	v->height_room = 0;
	init_struct2(v);
}

void		init_sdl(t_lemin *l, t_visu *v)
{
	int	flags;
	int	inited;

	flags = 0;
	inited = 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		free_all_msg(l, v, "Unable to initialize SDL :");
	else
		v->init_sdl = 1;
	flags = IMG_INIT_JPG | IMG_INIT_PNG;
	inited = IMG_Init(flags);
	if ((inited & flags) != flags)
		free_all_msg(l, v, "Failed to init required jpg and png support\n");
	else
		v->init_img = 1;
	if (TTF_Init() == -1)
		free_all_msg(l, v, "TFF_Init : ");
	else
		v->init_ttf = 1;
}

void		init_window(t_lemin *l, t_visu *v)
{
	if ((v->window = SDL_CreateWindow("Lem-in | @mdubus",
					SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH_W,
					HEIGHT_W, SDL_WINDOW_SHOWN)) == NULL)
		free_all_msg(l, v, "Unable to initialize window : ");
	else
		v->init_window = 1;
	if ((v->screen = SDL_CreateRenderer(v->window, -1, 0)) == NULL)
		free_all_msg(l, v, "Unable to create render : ");
	else
		v->init_screen = 1;
	v->typo = TTF_OpenFont("srcs/visualizer/typo.ttf", 40);
	if (!v->typo)
		free_all_msg(l, v, "Unable to initialize font : ");
	else
		v->init_typo = 1;
}
