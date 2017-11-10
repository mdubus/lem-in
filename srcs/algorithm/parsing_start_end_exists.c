/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_start_end.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:35:48 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/10 18:29:21 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	parsing_start_end_exists(t_lemin *l)
{
	if (ft_strstr(l->string_file, "##start") == 0)
	{
		ft_free_double_tab((void**)l->file);
		ft_memdel((void**)&l->string_file);
		error_lem_in(&ft_putendl_fd,
			"\033[091mErreur : Absence de la commande ##start\033[0m",
			STDERR_FILENO);
	}
	if (ft_strstr(l->string_file, "##end") == 0)
	{
		ft_free_double_tab((void**)l->file);
		ft_memdel((void**)&l->string_file);
		error_lem_in(&ft_putendl_fd,
			"\033[091mErreur : Absence de la commande ##end\033[0m",
			STDERR_FILENO);
	}
}
