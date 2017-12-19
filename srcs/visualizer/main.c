/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:19:51 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:19:52 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

int	main(void)
{
	t_visu		v;
	t_lemin		l;
	t_room_visu	*room;

	room = NULL;
	parsing_visu(&l, &v, room);
	ft_putendl(l.string_file);
	init_sdl(&l, &v);
	init_window(&l, &v);
	init_background(&l, &v);
	init_ant(&l, &v);
	draw_anthill(&l, &v);
	if ((SDL_RenderCopy(v.screen, v.all, NULL, NULL)) < 0)
		free_all_msg(&l, &v, "Error in main : ");
	v.coor = init_coor(v.begin_roomx, v.begin_roomy, v.width_room,
			v.height_room);
	if ((SDL_RenderCopy(v.screen, v.ant_img, NULL, &v.coor)) < 0)
		free_all_msg(&l, &v, "Error in main : ");
	draw_start_end_name(&l, &v);
	SDL_RenderPresent(v.screen);
	stock_ants(&l, &v);
	event_loop(&v, &l);
	free_all_and_quit(&l, &v);
}
