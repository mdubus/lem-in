/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:12:49 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:12:51 by mdubus           ###   ########.fr       */
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
