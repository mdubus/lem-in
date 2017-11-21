/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_parse_and_stock.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:17:33 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/17 17:18:35 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"

static void	which_command(t_lemin *l, int i)
{
	l->commands++;
	if (ft_strstr(l->f[i], "##start") != 0 && ft_strlen(l->f[i]) == 7)
		l->flag_start = 1;
	else if (ft_strstr(l->f[i], "##end") != 0 && ft_strlen(l->f[i]) == 5)
		l->flag_end = 1;
	else if (ft_strstr(l->f[i], "##lava") != 0 && ft_strlen(l->f[i]) == 6)
	{
		if (l->flag_snorlax == 1)
			l->flag_snorlax = 0;
		l->flag_lava = 1;
	}
	else if (ft_strstr(l->f[i], "##snorlax") != 0 && ft_strlen(l->f[i]) == 9)
	{
		if (l->flag_lava == 1)
			l->flag_lava = 0;
		l->flag_snorlax = 1;
	}
}

int			parsing_room_and_stock(t_lemin *l)
{
	int	i;

	i = l->start;
	while (l->f[i] != NULL)
	{
		if (l->f[i][0] && l->f[i][0] == '#' && l->f[i][1] && l->f[i][1] == '#')
			which_command(l, i);
		else if (l->f[i][0] && l->f[i][0] == '#' &&
				(!l->f[i][1] || (l->f[i][1] && l->f[i][1] != '#')))
			l->comments++;
		else if (ft_nb_occur_char_in_str(l->f[i], " ") == 2 &&
				l->f[i][0] && l->f[i][0] != '#')
			check_if_room(l->f[i], l);
		else if (l->f[i][0] && l->f[i][0] != '#' && ft_strstr(l->f[i], "-"))
		{
			l->start = i;
			return (1);
		}
		else
			return (2);
		i++;
	}
	l->start = i;
	return (0);
}
