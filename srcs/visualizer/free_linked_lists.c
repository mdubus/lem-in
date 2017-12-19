/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_linked_lists.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:19:29 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:19:30 by mdubus           ###   ########.fr       */
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

void	free_ants(t_visu *v)
{
	t_ant	*temp;

	temp = NULL;
	v->ant = v->ant_begin;
	while (v->ant)
	{
		temp = v->ant;
		v->ant = v->ant->next;
		free(temp);
	}
}
