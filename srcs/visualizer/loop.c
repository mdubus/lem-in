/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:19:46 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:19:47 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	reinit_anthill(t_lemin *l, t_visu *v)
{
	v->nb_ant_start = l->nb_ants;
	v->nb_ant_end = 0;
	if ((SDL_RenderClear(v->screen)) < 0)
		free_all_msg(l, v, "Error in move : ");
	if ((SDL_RenderCopy(v->screen, v->all, NULL, NULL)) < 0)
		free_all_msg(l, v, "Error in move : ");
	if (v->nb_ant_start > 0)
	{
		v->coor = init_coor(v->begin_roomx, v->begin_roomy, v->width_room,
				v->height_room);
		if ((SDL_RenderCopy(v->screen, v->ant_img, NULL, &v->coor)) < 0)
			free_all_msg(l, v, "Error in draw_ant_nb : ");
	}
	v->turn = v->turn_begin;
	v->ant = v->ant_begin;
	while (v->ant)
	{
		v->ant->nextx = -1;
		v->ant->nexty = -1;
		v->ant->prevx = -1;
		v->ant->prevy = -1;
		v->ant = v->ant->next;
	}
	draw_start_end_name(l, v);
	SDL_RenderPresent(v->screen);
}

static void	key_pressed(t_lemin *l, t_visu *v)
{
	if (v->event.key.keysym.sym == CLOSE)
		v->loop = false;
	else if (v->event.key.keysym.sym == RIGHT && v->turn)
		move_ant(l, v);
	else if (v->event.key.keysym.sym == R)
		reinit_anthill(l, v);
	else if (v->event.key.keysym.sym == PLUS || v->event.key.keysym.sym == 61)
		v->ant_speed += 1;
	else if (v->event.key.keysym.sym == MINUS || v->event.key.keysym.sym == 45)
	{
		v->ant_speed -= 1;
		if (v->ant_speed <= 0)
			v->ant_speed = 1;
	}
}

void		event_loop(t_visu *v, t_lemin *l)
{
	while (v->loop)
	{
		if (SDL_PollEvent(&(v->event)))
		{
			if (v->event.type == SDL_QUIT)
				v->loop = false;
			else if (v->event.type == SDL_KEYDOWN)
				key_pressed(l, v);
		}
		if (v->loop == false)
			break ;
		SDL_Delay(5);
	}
	if (v->loop == false)
		free_all_and_quit(l, v);
}
