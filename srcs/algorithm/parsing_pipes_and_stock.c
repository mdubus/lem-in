/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipes_and_stock.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 21:18:53 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/15 15:23:36 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"

static bool	**ft_create_tab_bool(unsigned long x, unsigned long y)
{
	bool	**tab;
	int		i;
	int		j;

	tab = NULL;
	i = 0;
	j = 0;
	tab = (bool **)malloc(sizeof(bool *) * (y + 1));
	if (tab == NULL)
		return (NULL);
	while ((unsigned long)i < y)
	{
		tab[i] = (bool *)malloc(sizeof(bool) * x);
		if (tab[i] == NULL)
		{
			ft_free_double_tab((void**)tab);
			return (NULL);
		}
		while ((unsigned long)j < x)
			tab[i][j++] = '\0';
		j = 0;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

static void	parsing_init_tab_pipes(t_lemin *l)
{
	l->pipes = ft_create_tab_bool((unsigned long)l->nb_rooms, (unsigned long)l->nb_rooms);
	if (l->pipes == NULL)
	{
		ft_free_double_tab((void**)l->eq);
		free_check_if_room(l,
				"\033[091mErreur lors d'une allocation memoire\033[0m");
	}
	l->room = l->begin;
	l->pipes[l->nb_rooms] = NULL;
}

static void	check_if_rooms_exists(t_lemin *l, char **tab)
{
	int		flag_room1;
	int		flag_room2;

	flag_room1 = -1;
	flag_room2 = -1;
	l->room = l->begin;
	while (l->room)
	{
		if (ft_strcmp(l->room->name, tab[0]) == 0)
			flag_room1 = l->room->id;
		if (ft_strcmp(l->room->name, tab[1]) == 0)
			flag_room2 = l->room->id;
		l->room = l->room->next;
	}
	l->room = l->begin;
	if (flag_room1 == -1 || flag_room2 == -1)
	{
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)tab);
		ft_free_double_tab((void**)l->pipes);
		free_check_if_room(l,
				"\033[091mErreur : Un ou plusieurs tubes sont lies a des salles inconnues\033[0m");
	}
	l->pipes[flag_room2][flag_room1] = 1;
	l->pipes[flag_room1][flag_room2] = 1;
}

static void	stock_pipes(char *str, t_lemin *l)
{
	char	**tab;

	tab = NULL;
	tab = ft_strsplit(str, '-');
	if (tab == NULL || tab[0] == NULL || tab[1] == NULL)
	{
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		free_check_if_room(l,
				"\033[091mErreur lors d'une allocation memoire\033[0m");
	}
	if (ft_strcmp(tab[0], tab[1]) == 0) // case salle reliee a elle meme
	{
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		ft_free_double_tab((void**)tab);
		free_check_if_room(l,
				"\033[091mErreur : Une salle ne peut pas etre reliee a elle-meme\
				\033[0m");
	}
	if (ft_nb_occur_char_in_str(str, "-") > 1) // case salle--salle
	{
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		ft_free_double_tab((void**)tab);
		free_check_if_room(l,
				"\033[091mErreur : Un ou plusieurs tubes sont mal formates\033[0m");
	}
	check_if_rooms_exists(l, tab);
	ft_free_double_tab((void**)tab);
	l->nb_pipes++;
}

int			parsing_pipes_and_stock(t_lemin *l)
{
	int	i;

	i = l->start;
	parsing_init_tab_pipes(l);
	while (l->file[i] != NULL)
	{
		if (ft_strstr(l->file[i], "##start") != 0 && ft_strlen(l->file[i]) == 7)
		{
			ft_free_double_tab((void**)l->eq);
			ft_free_double_tab((void**)l->pipes);
			free_check_if_room(l,
					"\033[091mErreur : Veuillez indiquer une salle de depart valide\033[0m");
		}
		else if (ft_strstr(l->file[i], "##end") != 0 && ft_strlen(l->file[i]) == 5)
		{
			ft_free_double_tab((void**)l->eq);
			ft_free_double_tab((void**)l->pipes);
			free_check_if_room(l,
					"\033[091mErreur : Veuillez indiquer une salle de fin valide\033[0m");
		}
		else if (l->file[i][0] && l->file[i][0] == '#' && 
				(!l->file[i][1] || (l->file[i][1] && l->file[i][1] != '#')))
			i++;
		else if (l->file[i][0] && l->file[i][0] == '#' && l->file[i][1] && l->file[i][1] == '#')
			i++;
		else if (ft_nb_occur_char_in_str(l->file[i], " ") == 2 && l->file[i][0] && l->file[i][0] != '#')
		{
			ft_free_double_tab((void**)l->eq);
			ft_free_double_tab((void**)l->pipes);
			free_check_if_room(l,
					"\033[091mErreur : La map est mal formatee\033[0m");
		}
		else if (l->file[i][0] && l->file[i][0] != '#' && ft_strstr(l->file[i], "-"))
			stock_pipes(l->file[i++], l);
		else
			return (1);
	}
	return (0);
}
