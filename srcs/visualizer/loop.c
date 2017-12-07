/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 11:19:22 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/07 18:41:04 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	move_ant(t_visu *v, int i)
{
	t_room_visu		*room;

	room = v->begin;
	if (!v->ant_begin)
	{
		v->ant = (t_ant*)malloc(sizeof(t_ant));
		v->ant_begin = v->ant;
	}
	else
	{
		v->ant->next = (t_ant*)malloc(sizeof(t_ant));
		v->ant = v->ant->next;
	}
	v->ant->next = NULL;
	if (!v->turn->prev || v->turn->prev->turn[i] == -1)
	{
		while (room)
		{
			if (room->special == START)
			{
				ft_putendl(room->name);
				v->first = room;
			}
			if (room->id == v->turn->turn[i])
				v->next = room;
			room = room->next;
		}
	}
	printf("prev x = %d, y = %d\n", v->first->x, v->first->y);
	printf("next x = %d, y = %d\n", v->next->x, v->next->y);
	v->ant->prevx = v->first->x;
	v->ant->prevy = v->first->y;
	v->ant->nextx = v->next->x;
	v->ant->nexty = v->next->y;
	v->ant->id = i;
}

void	move_ant_right(t_lemin *l, t_visu *v)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	(void)l;
	if (v->flag_move_right == 1 && v->turn->next)
	{
		if (v->turn == v->turn_begin)
		{
			while (i <= l->nb_ants)
			{
				if (v->turn->turn[i] != -1)
					move_ant(v, i);
				i++;
			}
		}
		v->flag_move_right = 0;
		if (v->ant_begin)
			v->loop_moving = 1;
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
		if (v->loop_moving == 1)
		{
			bool flag;

			flag = 0;
			v->ant = v->ant_begin;
			while (v->ant)
			{
				printf("\n** %d** \n", v->ant->id);
				printf("avant : x = %d, y = %d\n", v->ant->prevx, v->ant->prevy);
				printf("apres : x = %d, y = %d\n", v->ant->nextx, v->ant->nexty);
				if (v->ant->prevx > v->ant->nextx)
				{
					v->ant->prevx -= v->ant_speed;
					if (v->ant->prevx < v->ant->nextx)
						v->ant->prevx = v->ant->nextx;
					flag = 1;
				}
				else if (v->ant->prevx < v->ant->nextx)
				{
					v->ant->prevx += v->ant_speed;
					if (v->ant->prevx > v->ant->nextx)
						v->ant->prevx = v->ant->nextx;
					flag = 1;
				}
				if (v->ant->prevy > v->ant->nexty)
				{
					v->ant->prevy -= v->ant_speed;
					if (v->ant->prevy < v->ant->nexty)
						v->ant->prevy = v->ant->nexty;
					flag = 1;
				}
				else if (v->ant->prevy < v->ant->nexty)
				{
					v->ant->prevy += v->ant_speed;
					if (v->ant->prevy > v->ant->nexty)
						v->ant->prevy = v->ant->nexty;
					flag = 1;
				}
				if (flag == 1)
				{
					v->coor = init_coor(v->ant->prevx, v->ant->prevy, v->width_room, v->height_room);
					SDL_RenderCopy(v->screen, v->ant_img, NULL, &v->coor);
					SDL_RenderPresent(v->screen);
				}
				v->ant = v->ant->next;
			}
			if (flag == 0)
			{
				while (v->ant_begin)
				{
					v->ant = v->ant_begin;
					v->ant_begin = v->ant_begin->next;
					free(v->ant);
				}
				v->loop_moving = 0;
			}
		}
		SDL_Delay(5);
	}
	if (v->loop == false)
		free_all_and_quit(l, v);
}
