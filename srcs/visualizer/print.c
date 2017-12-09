/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 18:11:45 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/09 16:35:25 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

void	print_turns(t_lemin *l, t_visu *v)
{
	t_turn	*turn;
	int		i;

	i = 0;
	turn = v->turn_begin;
	while (i <= l->nb_ants)
		ft_printf("%2d ", i++);
	ft_putendl("(ant)");
	i = 0;
	while (turn)
	{
		while (i <= l->nb_ants)
			ft_printf("%2d ", turn->turn[i++]);
		turn = turn->next;
		i = 0;
		ft_putchar('\n');
	}
	v->turn = v->turn_begin;
}

void	print_rooms(t_visu *v)
{
	t_room_visu	*room;

	room = v->begin;
	while (room)
	{
		ft_printf("%d : %s\n", room->id, room->name);
		ft_printf("x = %d, y = %d\n", room->x, room->y);
		ft_printf("special = %d\n\n", room->special);
		room = room->next;
	}
	ft_printf("*************************\n");
}
