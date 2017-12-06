/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 11:19:22 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/06 17:45:37 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

void	move_ant_right(t_lemin *l, t_visu *v)
{
	(void)l;
	if (v->flag_move_right == 1)
	{
		if (!v->turn->next)
			printf("NULL\n");
		else
		{
			printf("OK\n");
			v->turn = v->turn->next;
		}
		v->flag_move_right = 0;
	}
}

void	move_ant_left(t_lemin *l, t_visu *v)
{
	(void)l;
	if (v->flag_move_left == 1)
	{
		if (!v->turn->prev)
			printf("NULL\n");
		else
		{
			printf("OK\n");
			v->turn = v->turn->prev;
		}
		v->flag_move_left = 0;
	}
}

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
					v->flag_move_right = 1;
				else if (v->event.key.keysym.sym == LEFT)
					v->flag_move_left = 1;
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
		if (v->flag_move_right == 1)
		{
			move_ant_right(l, v);
		}
		if (v->flag_move_left == 1)
		{
			move_ant_left(l, v);
		}
		SDL_Delay(5);
	}
	if (v->loop == false)
		free_all_and_quit(l, v);
}
