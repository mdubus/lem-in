/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_parsing_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:38:29 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/23 18:39:20 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

static void	free_in_pipes(t_lemin *l, char *str, t_visu *v)
{
	free(l->string_file);
	ft_free_double_tab((void**)l->f);
	free_rooms(v);
	error_lem_in(ft_putendl_fd, str, STDERR_FILENO, l);
}

int	visu_parsing_pipes(t_lemin *l, t_visu *v)
{
	int	i;

	i = l->start;
	while (l->f[i] != NULL)
	{
		if (ft_strstr(l->f[i], "##start") != 0 && ft_strlen(l->f[i]) == 7)
			free_in_pipes(l, "\033[091mErreur : start invalide\033[0m", v);
		else if (ft_strstr(l->f[i], "##end") != 0 && ft_strlen(l->f[i]) == 5)
			free_in_pipes(l, "\033[091mErreur : end invalide\033[0m", v);
		else if (l->f[i][0] && l->f[i][0] == '#' &&
				(!l->f[i][1] || (l->f[i][1] && l->f[i][1] != '#')))
			i++;
		else if (l->f[i][0] && l->f[i][0] == '#' &&
				l->f[i][1] && l->f[i][1] == '#')
			i++;
		else if (ft_nb_occur_char_in_str(l->f[i], " ") == 2 &&
				l->f[i][0] && l->f[i][0] != '#')
			free_in_pipes(l, "\033[091mErreur : Map mal formatee\033[0m", v);
		else if (l->f[i][0] && l->f[i][0] != '#' && ft_strstr(l->f[i], "-"))
			i++;
		else
			return (1);
	}
	return (0);
}
