/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 20:29:25 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/14 16:12:07 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	print_links(t_lemin *l, bool **pipes)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (i < l->nb_rooms)
	{
		while (j < l->nb_rooms)
		{
			if (pipes[i][j] == 1)
			{
				ft_putchar_fd('"', STDERR_FILENO);
				ft_putstr_fd(l->eq[i], STDERR_FILENO);
				ft_putstr_fd("\" -> \"", STDERR_FILENO);
				ft_putstr_fd(l->eq[j], STDERR_FILENO);
				ft_putstr_fd("\"\n", STDERR_FILENO);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

static void	print_rooms(t_lemin *l)
{
	int i;

	i = 0;
	while (i < l->nb_rooms)
	{
		if (i != l->room_start && i != l->room_end)
		{
			ft_putchar_fd('"', STDERR_FILENO);
			ft_putstr_fd(l->eq[i], STDERR_FILENO);
			ft_putstr_fd("\";\n", STDERR_FILENO);
		}
		i++;
	}
}

void		export_graph(bool **pipes, t_lemin *l)
{
	ft_putendl_fd("digraph callgraph {", STDERR_FILENO);
	ft_putendl_fd("concentrate=true", STDERR_FILENO);
	ft_putendl_fd("edge [arrowhead=none];", STDERR_FILENO);
	ft_putendl_fd("graph [splines=polyline];", STDERR_FILENO);
	ft_putendl_fd("node [shape = record, style=filled, ", STDERR_FILENO);
	ft_putendl_fd("color=lightblue2, fillcolor=lightblue2];", STDERR_FILENO);
	print_links(l, pipes);
	ft_putchar_fd('"', STDERR_FILENO);
	ft_putstr_fd(l->eq[l->room_start], STDERR_FILENO);
	ft_putstr_fd("\" [fillcolor=\"#3A539B\", color=\"#3A539B\"", STDERR_FILENO);
	ft_putstr_fd(", fontcolor=\"white\"];\n", STDERR_FILENO);
	ft_putchar_fd('"', STDERR_FILENO);
	ft_putstr_fd(l->eq[l->room_end], STDERR_FILENO);
	ft_putstr_fd("\" [fillcolor=\"#3A539B\", ", STDERR_FILENO);
	ft_putstr_fd("color=\"#3A539B\", fontcolor=\"white\"];\n", STDERR_FILENO);
	print_rooms(l);
	ft_putchar_fd('}', STDERR_FILENO);
}
