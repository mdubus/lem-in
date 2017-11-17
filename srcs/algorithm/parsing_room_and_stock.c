/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_parse_and_stock.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:17:33 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/17 14:38:33 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"

static void	which_command(t_lemin *l, int i)
{
	l->commands++;
	if (ft_strstr(l->file[i], "##start") != 0 && ft_strlen(l->file[i]) == 7)
		l->flag_start = 1;
	else if (ft_strstr(l->file[i], "##end") != 0 && ft_strlen(l->file[i]) == 5)
		l->flag_end = 1;
	else if (ft_strstr(l->file[i], "##lava") != 0 && ft_strlen(l->file[i]) == 6)
		l->flag_lava = 1;
	else if (ft_strstr(l->file[i], "##snorlax") != 0 &&
			ft_strlen(l->file[i]) == 9)
		l->flag_snorlax = 1;
}

int			parsing_room_and_stock(t_lemin *l)
{
	int	i;

	i = l->start;
	while (l->file[i] != NULL)
	{
		if (l->file[i][0] && l->file[i][0] == '#' && l->file[i][1] && l->file[i][1] == '#')
			which_command(l, i);
		else if (l->file[i][0] && l->file[i][0] == '#' &&
				(!l->file[i][1] || (l->file[i][1] && l->file[i][1] != '#')))
			l->comments++;
		else if (ft_nb_occur_char_in_str(l->file[i], " ") == 2 &&
				l->file[i][0] && l->file[i][0] != '#')
			check_if_room(l->file[i], l);
		else if (l->file[i][0] && l->file[i][0] != '#' && ft_strstr(l->file[i], "-"))
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
