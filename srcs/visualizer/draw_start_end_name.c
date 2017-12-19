/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_start_end_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:19:17 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:19:18 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	print_nb_ants(t_lemin *l, t_visu *v, t_room_visu *room,
		SDL_Surface **temp)
{
	char		*nb_ant;

	nb_ant = ft_strjoin(room->name, " (");
	if (room->special == START)
		nb_ant = ft_strjoin_proper(nb_ant, 1, ft_itoa(v->nb_ant_start), 1);
	else if (room->special == END)
		nb_ant = ft_strjoin_proper(nb_ant, 1, ft_itoa(v->nb_ant_end), 1);
	nb_ant = ft_strjoin_proper(nb_ant, 1, ")", 0);
	if (TTF_SizeText(v->typo, nb_ant, &v->coor.w, &v->coor.h) == -1)
		free_all_msg(l, v, "Error in print_nb_ants : ");
	v->coor.y = room->y + v->height_room + 5;
	v->coor.x = room->x + ((v->width_room - v->coor.w) / 2);
	if ((*temp = TTF_RenderText_Blended(v->typo, nb_ant, v->white)) == NULL)
		free_all_msg(l, v, "Error in print_nb_ants : ");
	free(nb_ant);
}

void		draw_start_end_name(t_lemin *l, t_visu *v)
{
	SDL_Surface	*temp;
	t_room_visu	*room;

	room = v->begin;
	temp = NULL;
	(void)l;
	while (room)
	{
		if (room->special == START || room->special == END)
		{
			print_nb_ants(l, v, room, &temp);
			if ((v->texture = SDL_CreateTextureFromSurface(v->screen,
							temp)) == NULL)
				free_all_msg(l, v, "Error in draw_start_end_name : ");
			if ((SDL_RenderCopy(v->screen, v->texture, NULL, &v->coor)) < 0)
				free_all_msg(l, v, "Error in draw_start_end_name : ");
			SDL_FreeSurface(temp);
			SDL_DestroyTexture(v->texture);
		}
		room = room->next;
	}
}
