/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_turns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:20:30 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:20:31 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	free_stock_turn(t_lemin *l, char *str, t_visu *v)
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
	free_in_pipes(l, str, v);
}

static void	create_turn(t_lemin *l, t_visu *v)
{
	int	i;

	i = 0;
	if (!v->turn_begin)
	{
		v->turn = (t_turn*)malloc(sizeof(t_turn));
		if (!v->turn)
			free_in_pipes(l, "Error with malloc", v);
		v->turn_begin = v->turn;
		v->turn->prev = NULL;
	}
	else
	{
		v->turn->next = (t_turn*)malloc(sizeof(t_turn));
		if (!v->turn->next)
			free_in_pipes(l, "Error with malloc", v);
		v->turn->next->prev = v->turn;
		v->turn = v->turn->next;
	}
	v->turn->next = NULL;
	v->turn->turn = (int*)malloc(sizeof(int) * (unsigned long)(l->nb_ants + 1));
	if (!v->turn->turn)
		free_stock_turn(l, "Error with malloc", v);
	while (i <= l->nb_ants)
		v->turn->turn[i++] = -1;
}

static void	parse_room_result(char *tab, int ant, t_lemin *l, t_visu *v)
{
	t_room_visu	*room_visu;
	char		*room;

	room = ft_strdup(ft_strchr(tab, '-') + 1);
	room_visu = v->begin;
	while (room_visu && (ft_strstr(room_visu->name, room) == 0))
		room_visu = room_visu->next;
	if (!room_visu)
		free_stock_turn(l, "\033[091mErreur : room inconnue\033[0m", v);
	if (ft_strstr(room_visu->name, room) != 0)
		v->turn->turn[ant] = room_visu->id;
	free(room);
}

static void	stock_turn(t_lemin *l, t_visu *v, char *str)
{
	char		**tab;
	int			i;
	int			ant;

	tab = NULL;
	i = 0;
	create_turn(l, v);
	if ((tab = ft_strsplit(str, ' ')) == NULL)
		free_stock_turn(l, "Error with malloc", v);
	if (ft_strchr(tab[i], '-') == 0)
		free_stock_turn(l, "Error in stock_turn", v);
	while (tab[i] && tab[i][1])
	{
		if (tab[i][0] != 'L')
			free_stock_turn(l, "\033[091mErreur : fourmi invalide\033[0m", v);
		ant = ft_atoi(&tab[i][1]);
		if (ant > l->nb_ants)
			free_stock_turn(l, "\033[091mErreur : fourmi invalide\033[0m", v);
		parse_room_result(tab[i], ant, l, v);
		i++;
	}
	ft_free_double_tab((void **)tab);
}

void		stock_turns(t_lemin *l, t_visu *v)
{
	int	i;

	i = l->start;
	while (l->f[i] && l->f[i][0] != 'L')
		i++;
	if (l->f[i] && l->f[i][0] && l->f[i][0] == 'L')
	{
		while (l->f[i])
		{
			stock_turn(l, v, l->f[i]);
			i++;
		}
	}
	else
		free_in_pipes(l, "\033[091mErreur : pas de resultat\033[0m", v);
	v->turn = v->turn_begin;
}
