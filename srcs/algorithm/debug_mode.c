/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:28:02 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/14 16:12:01 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	print_debug(t_lemin *l)
{
	print_resume(l);
	print_equivalence_tab(l);
	ft_print_tab_pipes(l);
	print_possible_paths(l);
	resolve(l);
	print_result(l);
	ft_putendl("\033[94m---------- Resultat ----------\n\033[0m");
}
