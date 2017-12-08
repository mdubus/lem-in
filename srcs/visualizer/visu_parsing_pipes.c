/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_parsing_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:38:29 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/08 14:57:21 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	check_if_rooms_exists(t_lemin *l, char **tab, t_visu *v)
{
	t_room_visu	*room;

	room = v->begin;
	l->flag_room1 = -1;
	l->flag_room2 = -1;
	while (room)
	{
		if (ft_strcmp(room->name, tab[0]) == 0)
			l->flag_room1 = room->id;
		if (ft_strcmp(room->name, tab[1]) == 0)
			l->flag_room2 = room->id;
		room = room->next;
	}
	room = v->begin;
	if (l->flag_room1 == -1 || l->flag_room2 == -1)
	{
		ft_free_double_tab((void**)tab);
		free_in_pipes(l,
				"\033[091mErreur : Tubes lies a des salles inconnues\033[0m", v);
	}
	if (l->flag_room1 != l->room_lava && l->flag_room2 != l->room_lava &&
			l->flag_room1 != l->room_snorlax && l->flag_room2 != l->room_snorlax)
	{
		l->pipes[l->flag_room2][l->flag_room1] = 1;
		l->pipes[l->flag_room1][l->flag_room2] = 1;
	}
}

void	stock_pipes_visu(char *str, t_lemin *l, t_visu *v)
{
	char	**tab;

	tab = NULL;
	tab = ft_strsplit(str, '-');
	if (!tab || tab == NULL || tab[0] == NULL || tab[1] == NULL)
	{
		free_in_pipes(l,
				"\033[091mErreur lors d'une allocation memoire\033[0m", v);
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
	check_if_rooms_exists(l, tab, v);
	ft_free_double_tab((void**)tab);
	l->nb_pipes++;
}

int	visu_parsing_pipes(t_lemin *l, t_visu *v)
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
		else if (l->f[i][0] && l->f[i][0] == '#' &&
				(!l->f[i][1] || (l->f[i][1] && l->f[i][1] != '#')))
			i++;
		else if (l->f[i][0] && l->f[i][0] == '#' &&
				l->f[i][1] && l->f[i][1] == '#')
			i++;
		else if (ft_nb_occur_char_in_str(l->f[i], " ") == 2 &&
				l->f[i][0] && l->f[i][0] != '#')
			free_in_pipes(l, "\033[091mErreur : Map mal formatee\033[0m", v);
		else if (l->f[i][0] && l->f[i][0] != '#' && ft_strstr(l->f[i], "-"))
			stock_pipes_visu(l->f[i++], l, v);
		else
		{
			l->start = i;
			return (1);
		}
	}
	l->start = i;
	return (0);
}
