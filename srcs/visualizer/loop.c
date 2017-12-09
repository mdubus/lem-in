/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 11:19:22 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/09 17:15:22 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	put_new_coor_ant(t_visu *v, int i)
{
	t_room_visu	*room;
	int			j;

	v->ant = v->ant_begin;
	j = i;
	if (v->turn->turn[i] == v->end_room_id)
	{
		v->ant_end++;
	}
	while (j > 1 && v->ant->next)
	{
		v->ant = v->ant->next;
		j--;
	}
	room = v->begin;
	while (room && room->id != v->turn->turn[i])
		room = room->next;
	v->ant->nextx = room->x;
	v->ant->nexty = room->y;
}

static void	draw_ant_nb(t_lemin *l, t_visu *v, int flag)
{
	if (v->nb_ant_start > 0)
	{
		v->coor = init_coor(v->begin_roomx, v->begin_roomy, v->width_room, v->height_room);
		if ((SDL_RenderCopy(v->screen, v->ant_img, NULL, &v->coor)) < 0)
			free_all_msg(l, v, "Error in draw_ant_nb : ");
	}
	if (v->nb_ant_end > 0)
	{
		v->coor = init_coor(v->end_roomx, v->end_roomy, v->width_room, v->height_room);
		if ((SDL_RenderCopy(v->screen, v->ant_img, NULL, &v->coor)) < 0)
			free_all_msg(l, v, "Error in draw_ant_nb : ");
	}
	if (!v->ant && flag == 1)
	{
		v->nb_ant_end += v->ant_end;
		v->ant_end = 0;
	}
	draw_start_end_name(l, v);
}

static void	move(t_lemin *l, t_visu *v)
{
	bool	flag;

	flag = 0;
	while (flag == 0)
	{
		flag = 1;
		v->ant = v->ant_begin;
		if ((SDL_RenderClear(v->screen)) < 0)
			free_all_msg(l, v, "Error in move : ");
		if ((SDL_RenderCopy(v->screen, v->all, NULL, NULL)) < 0)
			free_all_msg(l, v, "Error in move : ");
		while (v->ant)
		{
			//	v->coor = init_coor(v->ant->prevx, v->ant->prevy, v->width_room, v->height_room);
			if (v->ant->prevx > v->ant->nextx)
			{
				v->ant->prevx -= v->ant_speed;
				if (v->ant->prevx < v->ant->nextx)
					v->ant->prevx = v->ant->nextx;
				flag = 0;
			}
			else if (v->ant->prevx < v->ant->nextx)
			{
				v->ant->prevx += v->ant_speed;
				if (v->ant->prevx > v->ant->nextx)
					v->ant->prevx = v->ant->nextx;
				flag = 0;
			}
			if (v->ant->prevy > v->ant->nexty)
			{
				v->ant->prevy -= v->ant_speed;
				if (v->ant->prevy < v->ant->nexty)
					v->ant->prevy = v->ant->nexty;
				flag = 0;
			}
			else if (v->ant->prevy < v->ant->nexty)
			{
				v->ant->prevy += v->ant_speed;
				if (v->ant->prevy > v->ant->nexty)
					v->ant->prevy = v->ant->nexty;
				flag = 0;
			}
			if (v->ant->prevx != -1 && v->ant->prevy != -1 && v->ant->nextx != -1 && v->ant->nexty != -1)
			{
				v->coor = init_coor(v->ant->prevx, v->ant->prevy, v->width_room, v->height_room);
				if ((SDL_RenderCopy(v->screen, v->ant_img, NULL, &v->coor)) < 0)
					free_all_msg(l, v, "Error in move : ");
			}
			v->ant = v->ant->next;
		}
		draw_ant_nb(l, v, flag);
		SDL_RenderPresent(v->screen);
		SDL_Delay(5);
	}
}

void	move_ant(t_lemin *l, t_visu *v, int key)
{
	int	i;

	i = 0;
	(void)key;
	while (i <= l->nb_ants)
	{
		if (v->turn->turn[i] != -1)
			put_new_coor_ant(v, i);
		i++;
	}
	v->ant = v->ant_begin;
	while (v->ant)
	{
		if ((v->ant->nextx != -1 && v->ant->prevx == -1) || (v->ant->nexty != -1 && v->ant->prevy == -1))
		{
			v->nb_ant_start--;
			v->ant->prevx = v->begin_roomx;
			v->ant->prevy = v->begin_roomy;
		}
		v->ant = v->ant->next;
	}
	move(l, v);
	v->turn = v->turn->next;
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
				else if (v->event.key.keysym.sym == RIGHT && v->turn)
					move_ant(l, v, RIGHT);
				else if (v->event.key.keysym.sym == LEFT && v->turn)
					move_ant(l, v, LEFT);
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
		SDL_Delay(5);
	}
	if (v->loop == false)
		free_all_and_quit(l, v);
}
