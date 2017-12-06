/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 11:19:22 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/06 11:53:43 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

void init_struct(t_visu *v)
{
	v->window = NULL;
	v->typo = NULL;
	v->white = init_color(255, 255, 255, 255);
	v->purple = init_color(215, 149, 242, 255);
	v->pink = init_color(237, 101, 162, 255);
	v->loop = true;
	v->x = 450;
	v->y = 400;
	v->background = NULL;
	v->ant = NULL;
	v->width_room = 0;
	v->height_room = 0;
	v->flag_move = 0;
	v->temps_actuel = 0;
	v->temps_precedent = 0;
	v->ant_speed = 4;
	v->string_file = NULL;
	v->file = NULL;
	v->begin = NULL;
	v->turn_begin = NULL;
	v->turn = NULL;
	v->init_sdl = 0;
	v->init_img = 0;
	v->init_ttf = 0;
	v->init_window = 0;
	v->init_screen = 0;
	v->init_typo = 0;
	v->init_background = 0;
	v->init_ant = 0;
	v->surf = NULL;
	v->texture = NULL;
}

void	init_SDL(t_lemin *l, t_visu *v)
{
	int	flags;
	int	inited;

	flags = 0;
	inited = 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_putstr("Unable to initialize SDL : ");
		ft_putendl(SDL_GetError());
		free_all_and_quit(l, v);
	}
	else
		v->init_sdl = 1;
	flags = IMG_INIT_JPG | IMG_INIT_PNG;
	inited = IMG_Init(flags);
	if ((inited & flags) != flags)
	{
		ft_putstr("Failed to init required jpg and png support\n");
		ft_putendl(IMG_GetError());
		free_all_and_quit(l, v);
	}
	else
		v->init_img = 1;
	if (TTF_Init() == -1)
	{
		ft_putstr("TFF_Init : ");
		ft_putendl(SDL_GetError());
		free_all_and_quit(l, v);
	}
	else
		v->init_ttf = 1;
}

void	init_window(t_lemin *l, t_visu *v)
{
	if ((v->window = SDL_CreateWindow("Lem-in", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, WIDTH_W, HEIGHT_W,
					SDL_WINDOW_SHOWN)) == NULL)
	{
		ft_putstr("Unable to initialize window : ");
		ft_putendl(SDL_GetError());
		free_all_and_quit(l, v);
	}
	else
		v->init_window = 1;
	if ((v->screen = SDL_CreateRenderer(v->window, -1, 0)) == NULL)
	{
		ft_putstr("Unable to create render : ");
		ft_putendl(SDL_GetError());
		free_all_and_quit(l, v);
	}
	else
		v->init_screen = 1;
}

void	init_typo(t_lemin *l, t_visu *v)
{
	v->typo = TTF_OpenFont("srcs/visualizer/typo.ttf", 40);
	if (!v->typo)
	{
		ft_putstr("Unable to initialize font : ");
		ft_putendl(SDL_GetError());
		free_all_and_quit(l, v);
	}
	else
		v->init_typo = 1;
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
	v->surf = background;
}

void	init_ant(t_lemin *l, t_visu *v)
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

void	init_snorlax(t_lemin *l, t_visu *v)
{
	SDL_Surface		*snor;

	snor = IMG_Load("srcs/visualizer/img/snorlax.png");
	if (!snor)
	{
		ft_putstr("Unable to initialize snorlax : ");
		ft_putendl(SDL_GetError());
		free_all_and_quit(l, v);
	}
	if ((v->snorlax = SDL_CreateTextureFromSurface(v->screen, snor)) == NULL)
	{
		ft_putstr("Unable to create snorlax texture : ");
		ft_putendl(SDL_GetError());
		free_all_and_quit(l, v);
	}
	else
		v->init_snorlax = 1;
	SDL_FreeSurface(snor);
}

void	init_lava(t_lemin *l, t_visu *v)
{
	SDL_Surface		*lava;

	lava = IMG_Load("srcs/visualizer/img/lava.png");
	if (!lava)
	{
		ft_putstr("Unable to initialize lava : ");
		ft_putendl(SDL_GetError());
		free_all_and_quit(l, v);
	}
	if ((v->lava = SDL_CreateTextureFromSurface(v->screen, lava)) == NULL)
	{
		ft_putstr("Unable to create lava texture : ");
		ft_putendl(SDL_GetError());
		free_all_and_quit(l, v);
	}
	else
		v->init_lava = 1;
	SDL_FreeSurface(lava);
}
