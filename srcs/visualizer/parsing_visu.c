/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_visu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:20:14 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/28 13:48:33 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	check_start_end(t_lemin *l)
{
	if (l->room_end == -1)
		free_check_if_room(l, "\033[091mErreur : Aucune salle de fin\033[0m]]");
	if (l->room_start == -1)
		free_check_if_room(l,
				"\033[091mErreur : Aucune salle de depart\033[0m]]");
	if (l->nb_rooms == 0)
		free_check_if_room(l, "\033[091mErreur : Aucune room\033[0m]]");
	if (l->room_start == l->room_end)
		free_check_if_room(l,
				"\033[091mErreur : Start et end identiques\033[0m]]");
}

static void	check_if_rooms_exists_visu(t_lemin *l, char **tab, t_visu *v)
{
	t_room_visu	*room;

	room = v->begin;
	l->froom1 = -1;
	l->froom2 = -1;
	while (room)
	{
		if (ft_strcmp(room->name, tab[0]) == 0)
			l->froom1 = room->id;
		if (ft_strcmp(room->name, tab[1]) == 0)
			l->froom2 = room->id;
		room = room->next;
	}
	if (l->froom1 == -1 || l->froom2 == -1)
	{
		ft_free_double_tab((void**)tab);
		free_in_pipes(l,
				"\033[091mErreur: Tubes lies a des salles inconnues\033[0m", v);
	}
	if (l->froom1 != -1 && l->froom2 != -1)
	{
		l->pipes[l->froom2][l->froom1] = 1;
		l->pipes[l->froom1][l->froom2] = 1;
	}
}

static void	stock_pipes_visu(char *str, t_lemin *l, t_visu *v)
{
	char	**tab;

	tab = NULL;
	tab = ft_strsplit(str, '-');
	if (!tab || tab == NULL || tab[0] == NULL || tab[1] == NULL)
	{
		free_in_pipes(l,
				"\033[091mErreur : dans les pipes\033[0m", v);
	}
	if (ft_strcmp(tab[0], tab[1]) == 0)
	{
		ft_free_double_tab((void**)tab);
		free_in_pipes(l, "\033[091mErreur : Une salle est reliee a elle-meme\
				\033[0m", v);
	}
	if (ft_nb_occur_char_in_str(str, "-") > 1)
	{
		ft_free_double_tab((void**)tab);
		free_in_pipes(l,
				"\033[091mErreur : Un ou plusieurs tubes sont mal formates\
				\033[0m", v);
	}
	check_if_rooms_exists_visu(l, tab, v);
	ft_free_double_tab((void**)tab);
	l->nb_pipes++;
}

static int	visu_parsing_pipes(t_lemin *l, t_visu *v)
{
	int	i;

	i = l->start;
	parsing_init_tab_pipes(l);
	while (l->f[i] != NULL)
	{
		if (ft_strstr(l->f[i], "##start") != 0 && ft_strlen(l->f[i]) == 7)
			free_in_pipes(l, "\033[091mErreur : start invalide\033[0m", v);
		else if (ft_strstr(l->f[i], "##end") != 0 && ft_strlen(l->f[i]) == 5)
			free_in_pipes(l, "\033[091mErreur : end invalide\033[0m", v);
		else if ((l->f[i][0] && l->f[i][0] == '#' && (!l->f[i][1] || (l->f[i][1]
				&& l->f[i][1] != '#'))) || (l->f[i][0] && l->f[i][0] == '#' &&
				l->f[i][1] && l->f[i][1] == '#'))
			i++;
		else if (ft_nb_occur_char_in_str(l->f[i], " ") == 2 &&
				l->f[i][0] && l->f[i][0] != '#')
			free_in_pipes(l, "\033[091mErreur : Map mal formatee\033[0m", v);
		else if (l->f[i][0] && l->f[i][0] != '#' && ft_strstr(l->f[i], "-"))
			stock_pipes_visu(l->f[i++], l, v);
		else
			return (i);
	}
	return (i);
}

void		parsing_visu(t_lemin *l, t_visu *v, t_room_visu *room)
{
	init_struct_lemin(l);
	init_struct(v);
	get_file(l);
	parsing_ants_number(l);
	v->nb_ant_start = l->nb_ants;
	if (visu_parsing_room_and_stock(l, &room, v) == 2)
		free_room_visu(l,
				"\033[091mErreur : La map est mal formatee\033[0m", v);
	if (l->nb_rooms > 15)
		free_room_visu(l,
				"\033[091mErreur : Trop de rooms\033[0m", v);
	l->start = visu_parsing_pipes(l, v);
	check_start_end(l);
	stock_turns(l, v);
}
