/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:43:06 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/15 15:23:08 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"

static void	get_string_file(t_lemin *l)
{
	l->string_file = ft_read_all_file(STDIN_FILENO);
	if (l->string_file == NULL)
		error_lem_in(&ft_putendl_fd,
				"\033[091mErreur lors de la lecture du fichier\033[0m",
				STDERR_FILENO, l);
}

static void	get_tab_file(t_lemin *l)
{
	l->file = ft_strsplit_strict(l->string_file, '\n');
	if (l->file == NULL)
	{
		ft_memdel((void**)&l->string_file);
		error_lem_in(ft_putendl_fd,
			"\033[091mErreur : Fichier invalide\033[0m", STDERR_FILENO, l);
	}
}

void		get_file(t_lemin *l)
{
	get_string_file(l);
	get_tab_file(l);
}
