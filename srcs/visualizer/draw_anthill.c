/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_anthill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:19:00 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:19:00 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	draw_menu(t_lemin *l, t_visu *v)
{
	SDL_Surface	*temp;
	char		*str;

	str = ft_strdup("+ - : change ant speed   |");
	str = ft_strjoin_proper(str, 1, "   right : next turn   |", 0);
	str = ft_strjoin_proper(str, 1, "   r : reinit anthill", 0);
	if (TTF_SizeText(v->typo, str, &v->coor.w, &v->coor.h) == -1)
		free_all_msg(l, v, "Error on draw_menu : ");
	v->coor.y = HEIGHT_W - v->coor.h - 10;
	v->coor.x = (WIDTH_W - v->coor.w) / 2;
	if ((temp = TTF_RenderText_Blended(v->typo, str, v->white)) == NULL)
		free_all_msg(l, v, "Error on draw_menu : ");
	if ((v->texture = SDL_CreateTextureFromSurface(v->screen, temp)) == NULL)
		free_all_msg(l, v, "Error on draw_menu : ");
	if ((SDL_RenderCopy(v->screen, v->texture, NULL, &v->coor)) < 0)
		free_all_msg(l, v, "Error on draw_menu : ");
	SDL_FreeSurface(temp);
	SDL_DestroyTexture(v->texture);
	free(str);
}

void		draw_anthill(t_lemin *l, t_visu *v)
{
	t_room_visu	*room;

	room = v->begin;
	if ((v->all = SDL_CreateTexture(v->screen, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, WIDTH_W, HEIGHT_W)) == NULL)
		free_all_msg(l, v, "Error on draw_anthill : ");
	v->init_all = 1;
	if ((SDL_SetRenderTarget(v->screen, v->all)) < 0)
		free_all_msg(l, v, "Error on draw_anthill : ");
	if ((SDL_RenderCopy(v->screen, v->background, NULL, NULL)) < 0)
		free_all_msg(l, v, "Error on draw_anthill : ");
	if ((SDL_SetRenderDrawColor(v->screen, 109, 90, 73, 255)) < 0)
		free_all_msg(l, v, "Error on draw_anthill : ");
	draw_pipes(l, v);
	while (room)
	{
		draw_room(l, v, room);
		draw_room_name(l, v, room);
		room = room->next;
	}
	draw_menu(l, v);
	if ((SDL_SetRenderTarget(v->screen, NULL)) < 0)
		free_all_msg(l, v, "Error on draw_anthill : ");
}
