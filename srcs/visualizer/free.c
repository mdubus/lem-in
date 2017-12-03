/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:31:32 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/29 18:04:21 by mdubus           ###   ########.fr       */
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
		temp = v->turn_begin;
		v->turn_begin = v->turn_begin->next;
		ft_memdel((void **)&temp->turn);
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

void	free_all_and_quit(t_lemin *l, t_visu *v)
{
	free(l->string_file);
	ft_free_double_tab((void**)l->f);
	ft_free_double_tab((void**)l->pipes);
	free_rooms(v);
	free_turns(v);
	SDL_DestroyWindow(v->window);
	SDL_FreeSurface(v->background);
	SDL_FreeSurface(v->ant);
	TTF_CloseFont(v->typo);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
//	sleep(60);
	exit(1);
}
