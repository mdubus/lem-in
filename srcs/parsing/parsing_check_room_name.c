/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_room_name.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:03:09 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/10 13:00:40 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	check_for_hyphen(char **tab, t_lemin *l)
{
	if (ft_strchr(tab[0], '-') != 0)
	{
		ft_free_double_tab((void**)tab);
		free_check_if_room(l,
			"\033[091mErreur : Un nom de salle ne peut pas contenir de tiret\
			\033[0m");
	}
}

void	check_if_name_already_exists(char **tab, t_lemin *l)
{
	t_room *temp;

	temp = l->begin;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, tab[0]) == 0)
		{
			ft_free_double_tab((void**)tab);
			free_check_if_room(l,
			"\033[091mErreur : Un nom de salle doit etre unique\033[0m");
		}
		temp = temp->next;
	}
}

void	check_begin_with_l(char *str, t_lemin *l)
{
	if (str[0] && str[0] == 'L')
		free_check_if_room(l,
			"\033[091mErreur : Un nom de salle ne peut pas commencer par 'L'\
			\033[0m");
}

void	check_is_print(char *str, t_lemin *l)
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
