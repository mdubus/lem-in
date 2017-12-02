/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 11:19:22 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/29 16:52:11 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

void init_struct(t_visu *v)
{
	v->window = NULL;
	v->surf = NULL;
	v->typo = NULL;
	v->white = init_color(255, 255, 255, 255);
	v->purple = init_color(215, 149, 242, 255);
	v->pink = init_color(237, 101, 162, 255);
	v->loop = true;
	v->x = 450;
	v->y = 400;
	v->background = NULL;
	v->ant = NULL;
	v->flag_move = 0;
	v->temps_actuel = 0;
	v->temps_precedent = 0;
	v->ant_speed = 4;
	v->string_file = NULL;
	v->file = NULL;
	v->begin = NULL;
	v->turn_begin = NULL;
	v->turn = NULL;
}

void	init_SDL(t_visu *v)
{
	int	flags;
	int	inited;

	flags = 0;
	inited = 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_putstr("Unable to initialize SDL : ");
		SDL_GetError();
	}
	flags = IMG_INIT_JPG | IMG_INIT_PNG;
	inited = IMG_Init(flags);
	if ((inited&flags) != flags)
	{
		ft_putstr("Failed to init required jpg and png support\n");
		IMG_GetError();
		SDL_Quit();
		exit(1);
	}
	if(TTF_Init() == -1)
	{
		ft_putstr("TFF_Init : ");
		ft_putendl(SDL_GetError());
	}
	v->background = IMG_Load("srcs/visualizer/img/background.png");
	if (!v->background)
		ft_putendl("impossible de load l'image");
	v->ant = IMG_Load("srcs/visualizer/img/ant2.png");
	if (!v->ant)
		ft_putendl("Impossible de load l'image");
	v->width_room = v->ant->w + 10;
	v->height_room = v->ant->h + 10;
}

void	init_window_and_surface(t_visu *v)
{
	if ((v->window = SDL_CreateWindow("Lem-in", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, WIDTH_W, HEIGHT_W,
					SDL_WINDOW_SHOWN)) == NULL)
	{
		ft_putstr("Unable to initialize window : ");
		ft_putendl(SDL_GetError());
	}
	if ((v->surf = SDL_GetWindowSurface(v->window)) == NULL)
	{
		ft_putstr("Unable to initialize surface : ");
		ft_putendl(SDL_GetError());
	}
	v->typo = TTF_OpenFont("srcs/visualizer/typo.ttf", 40);
	if (!v->typo)
	{
		ft_putstr("Unable to initialize font : ");
		ft_putendl(SDL_GetError());
	}
}
