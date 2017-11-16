/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 11:31:45 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/16 16:37:56 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"

void	init_struct_lemin(t_lemin *l)
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
	l->pipes = NULL;
	l->string_file = NULL;
	l->room_start = -1;
	l->room_end = -1;
	l->file = NULL;
	l->room = NULL;
	l->begin = NULL;
	l->sum = NULL;
	l->nb_path = 0;
	l->lookup = NULL;
	l->sorted = NULL;
	l->debug = 0;
	l->graph = 0;
	l->path = NULL;
	l->visited = NULL;
	l->level = NULL;
	l->flag_start_to_end = 0;
	l->best_path = NULL;
	l->solution = NULL;
	l->solution_begin = NULL;
}

void	init_arguments(int argc, char **argv, t_lemin *l)
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
