/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_if_room.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:03:01 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/08 18:33:48 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	check_coordonates(char **tab, t_lemin *l)
{
	int	ret;

	ret = -1;
	if (tab[1][0] && tab[1][0] == '-' && tab[1][1])
		ret = ft_check_if_num(&tab[1][1]);
	else
		ret = ft_check_if_num(tab[1]);
	if (ret != 0)
	{
		ft_free_tab_char(&tab);
		free_check_if_room(l,
			"\033[091mErreur : Une ou plusieurs coordonnees X sont incorrectes\
			\033[0m");
	}
	ret = -1;
	if (tab[2][0] && tab[2][0] == '-' && tab[2][1])
		ret = ft_check_if_num(&tab[2][1]);
	else
		ret = ft_check_if_num(tab[2]);
	if (ret != 0)
	{
		ft_free_tab_char(&tab);
		free_check_if_room(l,
			"\033[091mErreur : Une ou plusieurs coordonnees Y sont incorrectes\
			\033[0m");
	}
}

static void	check_for_hyphen(char **tab, t_lemin *l)
{
	if (ft_strchr(tab[0], '-') != 0)
	{
		ft_free_tab_char(&tab);
		free_check_if_room(l,
			"\033[091mErreur : Un nom de salle ne peut pas contenir de tiret\
			\033[0m");
	}
}

static void	check_if_name_already_exists(char **tab, t_lemin *l)
{
	t_room *temp;

	temp = l->begin;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, tab[0]) == 0)
		{
			ft_free_tab_char(&tab);
			free_check_if_room(l,
			"\033[091mErreur : Un nom de salle doit etre unique\033[0m");
		}
		temp = temp->next;
	}
}

static void	stock_room_name(t_lemin *l, char **tab)
{
	if (!l->begin)
	{
		l->room = (t_room*)malloc(sizeof(t_room));
		l->begin = l->room;
	}
	else
	{
		l->room->next = (t_room*)malloc(sizeof(t_room));
		l->room = l->room->next;
	}
	l->room->name = ft_strdup(tab[0]);
	l->id++;
	l->room->id = l->id;
	l->room->next = NULL;
	if (l->flag_start == 1)
	{
		l->room_start = l->room->id;
		l->flag_start = 0;
	}
	if (l->flag_end == 1)
	{
		l->room_end = l->room->id;
		l->flag_end = 0;
	}
	l->nb_rooms++;
}

static void	check_begin_with_l(char *str, t_lemin *l)
{
	if (str[0] && str[0] == 'L')
		free_check_if_room(l,
			"\033[091mErreur : Un nom de salle ne peut pas commencer par 'L'\
			\033[0m");
}

static void	check_is_print(char *str, t_lemin *l)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isprint(str[i]) == 0)
			flag = 1;
		i++;
	}
	if (flag == 1)
		free_check_if_room(l,
			"\033[091mErreur : Un ou plusieurs noms de salles sont invalides\
			\033[0m");
}


int			check_if_room(char *str, t_lemin *l)
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
	stock_room_name(l, tab);
	ft_free_tab_char(&tab);
	return (0);
}
