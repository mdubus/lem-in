/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:31:32 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/24 11:46:17 by mdubus           ###   ########.fr       */
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
		free(v->begin->name);
		v->begin = v->begin->next;
		free(temp);
	}
}

void	free_in_pipes(t_lemin *l, char *str, t_visu *v)
{
	free(l->string_file);
	ft_free_double_tab((void**)l->f);
	free_rooms(v);
	error_lem_in(ft_putendl_fd, str, STDERR_FILENO, l);
}
