/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:19:40 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:19:41 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

void	init_background(t_lemin *l, t_visu *v)
{
	SDL_Surface		*background;

	background = IMG_Load("srcs/visualizer/img/background.png");
	if (!background)
		free_all_msg(l, v, "Unable to initialize background : ");
	if ((v->background = SDL_CreateTextureFromSurface(v->screen,
					background)) == NULL)
		free_all_msg(l, v, "Unable to create background texture : ");
	else
		v->init_background = 1;
	v->surf = background;
}

void	init_ant(t_lemin *l, t_visu *v)
{
	SDL_Surface		*ant;

	ant = IMG_Load("srcs/visualizer/img/ant2.png");
	if (!ant)
		free_all_msg(l, v, "Unable to initialize ant : ");
	v->width_room = ant->w;
	v->height_room = ant->h;
	if ((v->ant_img = SDL_CreateTextureFromSurface(v->screen, ant)) == NULL)
		free_all_msg(l, v, "Unable to create ant texture : ");
	else
		v->init_ant = 1;
	SDL_FreeSurface(ant);
}

void	init_snorlax(t_lemin *l, t_visu *v)
{
	SDL_Surface		*snor;

	snor = IMG_Load("srcs/visualizer/img/snorlax.png");
	if (!snor)
		free_all_msg(l, v, "Unable to initialize snorlax : ");
	if ((v->snorlax = SDL_CreateTextureFromSurface(v->screen, snor)) == NULL)
		free_all_msg(l, v, "Unable to create snorlax texture : ");
	else
		v->init_snorlax = 1;
	SDL_FreeSurface(snor);
}

void	init_lava(t_lemin *l, t_visu *v)
{
	SDL_Surface		*lava;

	lava = IMG_Load("srcs/visualizer/img/lava.png");
	if (!lava)
		free_all_msg(l, v, "Unable to initialize lava : ");
	if ((v->lava = SDL_CreateTextureFromSurface(v->screen, lava)) == NULL)
		free_all_msg(l, v, "Unable to create lava texture : ");
	else
		v->init_lava = 1;
	SDL_FreeSurface(lava);
}
