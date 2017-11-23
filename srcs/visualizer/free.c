/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:31:32 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/23 18:36:46 by mdubus           ###   ########.fr       */
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
