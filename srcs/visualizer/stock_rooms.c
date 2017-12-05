/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 15:33:53 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/29 18:30:52 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	check_special_rooms(t_lemin *l, t_room_visu **room)
{
	if (l->flag_start == 1)
	{
		(*room)->special = START;
		l->flag_start = 0;
		l->room_start = (*room)->id;
	}
	if (l->flag_end == 1)
	{
		(*room)->special = END;
		l->flag_end = 0;
		l->room_end = (*room)->id;
	}
	if (l->flag_lava == 1)
	{
		(*room)->special = LAVA;
		l->flag_lava = 0;
	}
	if (l->flag_snorlax == 1)
	{
		(*room)->special = SNORLAX;
		l->flag_snorlax = 0;
	}
}

static void	stock_room(t_lemin *l, char **tab, t_room_visu **room, t_visu *v)
{
	if (!v->begin)
	{
		*room = (t_room_visu*)malloc(sizeof(t_room_visu));
		v->begin = *room;
	}
	else
	{
		(*room)->next = (t_room_visu*)malloc(sizeof(t_room_visu));
		*room = (*room)->next;
	}
	(*room)->name = ft_strdup(tab[0]);
	(*room)->id = l->id;
	l->id++;
	(*room)->next = NULL;
	(*room)->x = ft_atoi(tab[1]);
	(*room)->y = ft_atoi(tab[2]);
	(*room)->special = 0;
	check_special_rooms(l, room);
	l->nb_rooms++;
}

static int	visu_check_if_room(char *str, t_lemin *l, t_room_visu **room, t_visu *v)
{
	char	**tab;

	tab = NULL;
	check_begin_with_l(str, l);
	check_is_print(str, l);
	tab = ft_strsplit(str, ' ');
	if (tab == NULL || tab[0] == NULL || tab[1] == NULL || tab[2] == NULL)
		free_check_if_room(l,
			"\033[091mErreur lors de la recuperation d'une salle\033[0m");
	check_coordonates(tab, l);
	check_for_hyphen(tab, l);
	check_if_name_already_exists(tab, l);
	stock_room(l, tab, room, v);
	ft_free_double_tab((void**)tab);
	return (0);
}

int	visu_parsing_room_and_stock(t_lemin *l, t_room_visu **room, t_visu *v)
{
	int	i;

	i = l->start;
	while (l->f[i] != NULL)
	{
		if (l->f[i][0] && l->f[i][0] == '#' && l->f[i][1] && l->f[i][1] == '#')
			which_command(l, i);
		else if (l->f[i][0] && l->f[i][0] == '#' &&
				(!l->f[i][1] || (l->f[i][1] && l->f[i][1] != '#')))
			l->comments++;
		else if (ft_nb_occur_char_in_str(l->f[i], " ") == 2 &&
				l->f[i][0] && l->f[i][0] != '#')
			visu_check_if_room(l->f[i], l, room, v);
		else if (l->f[i][0] && l->f[i][0] != '#' && ft_strstr(l->f[i], "-"))
		{
			l->start = i;
			return (1);
		}
		else
			return (2);
		i++;
	}
	l->start = i;
	return (0);
}

