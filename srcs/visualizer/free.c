/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:31:32 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/09 17:24:47 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

void	free_in_pipes(t_lemin *l, char *str, t_visu *v)
{
	free(l->string_file);
	ft_free_double_tab((void**)l->f);
	ft_free_double_tab((void**)l->pipes);
	free_rooms(v);
	error_lem_in(ft_putendl_fd, str, STDERR_FILENO, l);
}

void	free_room_visu(t_lemin *l, char *str, t_visu *v)
{
	free(l->string_file);
	ft_free_double_tab((void**)l->f);
	free_rooms(v);
	error_lem_in(ft_putendl_fd, str, STDERR_FILENO, l);
}

void	free_parsing_visu(t_lemin *l, t_visu *v)
{
	free(l->string_file);
	ft_free_double_tab((void**)l->f);
	free_rooms(v);
	ft_free_double_tab((void**)l->pipes);
	free_turns(v);
}

void	free_all_msg(t_lemin *l, t_visu *v, char *str)
{
	ft_putstr(str);
	ft_putendl(SDL_GetError());
	free_all_and_quit(l, v);
}

void	free_all_and_quit(t_lemin *l, t_visu *v)
{
	free_parsing_visu(l, v);
	if (v->init_window == 1)
		SDL_DestroyWindow(v->window);
	if (v->init_screen == 1)
		SDL_DestroyRenderer(v->screen);
	if (v->init_background == 1)
	{
		SDL_DestroyTexture(v->background);
		SDL_FreeSurface(v->surf);
	}
	if (v->init_ant == 1)
		SDL_DestroyTexture(v->ant_img);
	if (v->init_snorlax == 1)
		SDL_DestroyTexture(v->snorlax);
	if (v->init_lava == 1)
		SDL_DestroyTexture(v->lava);
	if (v->init_all == 1)
		SDL_DestroyTexture(v->all);
	if (v->ants_stocked == 1)
		free_ants(v);
	if (v->init_ttf == 1)
		TTF_Quit();
	if (v->init_img == 1)
		IMG_Quit();
	if (v->init_sdl == 1)
		SDL_Quit();
//	sleep(60);
	exit(1);
}
