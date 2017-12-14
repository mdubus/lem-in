/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:24:26 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/14 17:29:41 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int	main(int argc, char **argv)
{
	t_lemin	l;

	init_struct_lemin(&l);
	init_arguments(argc, argv, &l);
	parsing(&l);
	remove_useless_paths(&l);
	if (l.debug == 1)
		print_debug(&l);
	else
		resolve(&l);
	ft_putendl(l.string_file);
	create_ant_result(&l);
	get_ants(&l);
	free_at_end(&l);
	free_result(&l);
	return (0);
}
