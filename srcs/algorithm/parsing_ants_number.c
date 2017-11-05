/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ants_number.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:34:49 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/05 12:05:23 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	case_ants_number_negative(t_lemin *l)
{
	if (l->nb_ants <= 0)
	{
		ft_free_tab_char(&l->file);
		ft_memdel((void**)&l->string_file);
		error_lem_in(ft_putendl_fd,
			"\033[091mErreur : Veuillez indiquer un nombre de fourmis correct\
			\033[0m", STDERR_FILENO);
	}
}

void		parsing_ants_number(t_lemin *l)
{
	while (l->file[l->start] && l->file[l->start][0] == '#')
		l->start++;
	if (ft_check_if_num(l->file[l->start]) == 1)
	{
		ft_free_tab_char(&l->file);
		ft_memdel((void**)&l->string_file);
		error_lem_in(ft_putendl_fd,
			"\033[091mErreur : Veuillez indiquer un nombre de fourmis correct\
			\033[0m", STDERR_FILENO);
	}
	else if (ft_strlen(l->file[l->start]) > 10)
	{
		ft_free_tab_char(&l->file);
		ft_memdel((void**)&l->string_file);
		error_lem_in(ft_putendl_fd,
		"\033[091mErreur : Il y a trop de fourmis dans la fourmilliere\
		\033[0m", STDERR_FILENO);
	}
	else
		l->nb_ants = ft_atoi(l->file[l->start]);
	case_ants_number_negative(l);
	l->start++;
}
