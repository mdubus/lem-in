/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:31:32 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/04 18:00:02 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

void	free_rooms(t_visu *v)
{
	t_room_visu	*temp;

	temp = NULL;
	while (v->begin)
	{
		temp = v->begin;
		v->begin = v->begin->next;
		free(temp->name);
		free(temp);
	}
}

void	free_turns(t_visu *v)
{
	t_turn	*temp;

	temp = NULL;
	while (v->turn_begin)
	{
		free(v->turn_begin->turn);
		temp = v->turn_begin;
		v->turn_begin = v->turn_begin->next;
		free(temp);
	}
}
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

void	free_all_and_quit(t_lemin *l, t_visu *v)
{
	free_parsing_visu(l, v);
	if (v->init_window == 1)
		SDL_DestroyWindow(v->window);
	if (v->init_screen == 1)
		SDL_DestroyRenderer(v->screen);
	if (v->init_background == 1)
		SDL_DestroyTexture(v->background);
	if (v->init_ant == 1)
		SDL_DestroyTexture(v->ant);
//	SDL_FreeSurface(v->background);
//	SDL_FreeSurface(v->ant);
//	TTF_CloseFont(v->typo);
	if (v->init_ttf == 1)
		TTF_Quit();
	if (v->init_img == 1)
		IMG_Quit();
	if (v->init_sdl == 1)
		atexit(SDL_Quit);
//	sleep(60);
	exit(1);
}
