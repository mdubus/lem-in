/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_end_and_start.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:20:41 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/17 14:32:13 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
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

void		check_end_and_start(t_lemin *l)
{
	case_no_rooms(l);
	case_no_pipes(l);
	case_no_end_start(l);
	case_start_end_identical(l);
}
