/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 11:19:22 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/29 18:10:15 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"


void event_loop(t_visu *v, t_lemin *l)
{
	while (v->loop)
	{
		if (SDL_PollEvent(&(v->event)))
		{
			if (v->event.type == SDL_QUIT)
				v->loop = false;
			else if (v->event.type == SDL_KEYDOWN)
			{
				if (v->event.key.keysym.sym == CLOSE)
					v->loop = false;
				else if (v->event.key.keysym.sym == RIGHT)
					v->flag_move = 1;
				else if (v->event.key.keysym.sym == PLUS)
					v->ant_speed += 1;
				else if (v->event.key.keysym.sym == MINUS)
				{
					v->ant_speed -= 1;
					if (v->ant_speed <= 0)
						v->ant_speed = 1;
				}
			}
		}
		if (v->loop == false)
			break ;
		if (v->flag_move == 1)
		{
			if (v->x <= 800 && v->y <= 700)
				move_ant(v);
			else
				v->flag_move = 0;
		}
		SDL_Delay(5);
	}
	if (v->loop == false)
		free_all_and_quit(l, v);
}
