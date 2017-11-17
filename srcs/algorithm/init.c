/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 11:31:45 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/17 17:13:57 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"

static void	init_struct_lemin2(t_lemin *l)
{
	l->nb_ants = 0;
	l->nb_pipes = 0;
	l->nb_rooms = 0;
	l->flag_start = -1;
	l->flag_end = -1;
	l->id = 0;
	l->comments = 0;
	l->commands = 0;
	l->start = 0;
	l->nb_path = 0;
	l->room_start = -1;
	l->room_end = -1;
	l->debug = 0;
	l->graph = 0;
	l->flag_start_to_end = 0;
	l->flag_lava = 0;
	l->flag_snorlax = 0;
	l->room_lava = -1;
	l->room_snorlax = -1;
	l->flag_room1 = -1;
	l->flag_room2 = -1;
}

void		init_struct_lemin(t_lemin *l)
{
	l->path = NULL;
	l->path_begin = NULL;
	l->best_path = NULL;
	l->solution = NULL;
	l->solution_begin = NULL;
	l->room = NULL;
	l->begin = NULL;
	l->sum = NULL;
	l->lookup = NULL;
	l->level = NULL;
	l->sorted = NULL;
	l->eq = NULL;
	l->f = NULL;
	l->string_file = NULL;
	l->pipes = NULL;
	l->visited = NULL;
	init_struct_lemin2(l);
}

void		init_arguments(int argc, char **argv, t_lemin *l)
{
	if (argc == 2)
	{
		if (ft_strcmp(argv[1], "usage") == 0)
		{
			ft_putendl("\033[094mUsage : \n");
			ft_putendl("-d : debug mode");
			ft_putendl("-g : export file for dot (graph)");
			ft_putstr("\033[0m");
			exit(1);
		}
		else if (argv[1][0] && argv[1][0] == '-')
		{
			if (ft_strchr(argv[1], 'd') != NULL)
				l->debug = 1;
			if (ft_strchr(argv[1], 'g') != NULL)
				l->graph = 1;
		}
	}
}
