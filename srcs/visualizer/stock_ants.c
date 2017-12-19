/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:20:19 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 18:10:41 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

void	stock_ants(t_lemin *l, t_visu *v)
{
	int	i;

	i = 0;
	while (i < l->nb_ants)
	{
		if (!v->ant_begin)
		{
			v->ant = (t_ant*)malloc(sizeof(t_ant));
			v->ant_begin = v->ant;
		}
		else
		{
			v->ant->next = (t_ant*)malloc(sizeof(t_ant));
			v->ant = v->ant->next;
		}
		v->ant->id = i + 1;
		v->ant->prevx = -1;
		v->ant->prevy = -1;
		v->ant->nextx = -1;
		v->ant->nexty = -1;
		v->ant->modx = -1;
		v->ant->mody = -1;
		v->ant->next = NULL;
		i++;
	}
	v->ants_stocked = 1;
}
