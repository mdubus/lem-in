/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:20:25 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/28 13:21:34 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	check_special_rooms(t_lemin *l, t_visu *v, t_room_visu **room)
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
		v->end_roomx = (*room)->x;
		v->end_roomy = (*room)->y;
		v->end_room_id = (*room)->id;
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

static void	stock_coordonates(t_lemin *l, char **tab, t_room_visu **room)
{
	(*room)->x = ft_latoi(tab[1]);
	(*room)->y = ft_latoi(tab[2]);
	if ((*room)->x > WIDTH_W || (*room)->x < 0 || (*room)->x > 2147483648 ||
			(*room)->y > HEIGHT_W || (*room)->y < 0 || (*room)->y > 2147483648)
	{
		ft_free_double_tab((void**)tab);
		free(l->string_file);
		free_lst_name(l);
		ft_putendl_fd("\033[091mErreur : Coordonnees invalides\033[0m",
				STDERR_FILENO);
		exit(1);
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
	(*room)->id = l->id++;
	(*room)->next = NULL;
	stock_coordonates(l, tab, room);
	(*room)->special = -1;
	check_special_rooms(l, v, room);
	l->nb_rooms++;
	if ((*room)->special == START)
	{
		v->begin_roomx = (*room)->x;
		v->begin_roomy = (*room)->y;
	}
}

static int	visu_check_if_room(char *str, t_lemin *l, t_room_visu **room,
		t_visu *v)
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

int			visu_parsing_room_and_stock(t_lemin *l, t_room_visu **room,
		t_visu *v)
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
