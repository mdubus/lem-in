/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_parse_and_stock.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:17:33 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/11 11:24:20 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	case_start_end_identical(t_lemin *l)
{
	if (l->room_start == l->room_end)
	{
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		ft_free_double_tab((void**)l->file);
		free(l->string_file);
		free_lst_name(l);
		error_lem_in(ft_putendl_fd,
				"\033[091mErreur : Les salles start et end sont identiques\033[0m",
				STDERR_FILENO, l);
	}
}

static void	case_no_rooms(t_lemin *l)
{
	if (l->nb_rooms == 0)
	{
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		ft_free_double_tab((void**)l->file);
		free(l->string_file);
		free_lst_name(l);
		error_lem_in(ft_putendl_fd,
				"\033[091mErreur : Aucune salle n'est presente\033[0m",
				STDERR_FILENO, l);
	}
}

static void	case_no_pipes(t_lemin *l)
{
	if (l->nb_pipes == 0)
	{
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		ft_free_double_tab((void**)l->file);
		free(l->string_file);
		free_lst_name(l);
		error_lem_in(ft_putendl_fd,
				"\033[091mErreur : Aucun tube n'est present\033[0m",
				STDERR_FILENO, l);
	}
}

static void	case_no_end_start(t_lemin *l)
{
	if (l->room_start == -1)
	{
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		ft_free_double_tab((void**)l->file);
		free(l->string_file);
		free_lst_name(l);
		error_lem_in(ft_putendl_fd,
				"\033[091mErreur : Aucune salle de depart\033[0m",
				STDERR_FILENO, l);
	}
	if (l->room_end == -1)
	{
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		ft_free_double_tab((void**)l->file);
		free(l->string_file);
		free_lst_name(l);
		error_lem_in(ft_putendl_fd,
				"\033[091mErreur : Aucune salle de fin\033[0m",
				STDERR_FILENO, l);
	}
}

void	check_end_and_start(t_lemin *l)
{
	case_no_rooms(l);
	case_no_pipes(l);
	case_no_end_start(l);
	case_start_end_identical(l);
	if (l->graph == 1)
		export_graph(l->pipes, l);
}

int		parsing_room_and_stock(t_lemin *l)
{
	int	i;

	i = l->start;
	while (l->file[i] != NULL)
	{
		if (ft_strstr(l->file[i], "##start") != 0 && ft_strlen(l->file[i]) == 7)
			l->flag_start = 1;
		else if (ft_strstr(l->file[i], "##end") != 0 && ft_strlen(l->file[i]) == 5)
			l->flag_end = 1;
		else if (l->file[i][0] && l->file[i][0] == '#' && 
				(!l->file[i][1] || (l->file[i][1] && l->file[i][1] != '#')))
			l->comments++;
		else if (l->file[i][0] && l->file[i][0] == '#' && l->file[i][1] && l->file[i][1] == '#')
			l->commands++;
		else if (ft_nb_occur_char_in_str(l->file[i], " ") == 2 && l->file[i][0] && l->file[i][0] != '#')
			check_if_room(l->file[i], l);
		else if (l->file[i][0] && l->file[i][0] != '#' && ft_strstr(l->file[i], "-"))
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
