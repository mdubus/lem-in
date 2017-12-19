/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_check_if_solution_exists.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:13:53 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:13:54 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void		already_explored(t_lemin *l, int *j, int room, int i)
{
	(*j)--;
	l->lookup[room] = -1;
	l->pipes[room][i] = 1;
	l->pipes[i][room] = 1;
}

static void	end_found(t_lemin *l, int *j, int room, int i)
{
	l->flag_start_to_end = 1;
	l->pipes[room][i] = 1;
	l->pipes[i][room] = 1;
	(*j)--;
	l->lookup[room] = -1;
}

void		back_in_stack(t_lemin *l, int *j, int room, int i)
{
	l->pipes[room][i] = 1;
	l->pipes[i][room] = 1;
	(*j)--;
	l->lookup[room] = -1;
}

static int	start_related_to_end(t_lemin *l, int room, int *j)
{
	int	i;

	i = 0;
	while (i < l->nb_rooms && l->flag_start_to_end == 0)
	{
		if (l->pipes[room][i] == 1)
		{
			(*j)++;
			if (room != l->room_start)
				l->lookup[room] = (*j - 1);
			l->pipes[room][i] = 0;
			l->pipes[i][room] = 0;
			if (i == l->room_end)
				end_found(l, j, room, i);
			else if (l->lookup[i] > 0 || i == l->room_start)
				already_explored(l, j, room, i);
			else
			{
				start_related_to_end(l, i, j);
				back_in_stack(l, j, room, i);
			}
		}
		i++;
	}
	return (l->flag_start_to_end);
}

void		check_if_solution_exists(t_lemin *l)
{
	int i;
	int j;
	int	ret;

	i = 0;
	j = 0;
	ret = 0;
	l->lookup = (int *)malloc(sizeof(int) * (unsigned long)(l->nb_rooms));
	while (i < l->nb_rooms)
		l->lookup[i++] = -1;
	ret = start_related_to_end(l, l->room_start, &j);
	free(l->lookup);
	if (ret == 0)
	{
		free(l->sum);
		ft_memdel((void**)&l->string_file);
		ft_free_double_tab((void**)l->f);
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		free_lst_name(l);
		error_lem_in(ft_putendl_fd,
				"\033[091mErreur : start et end ne sont pas relies\033[0m",
				STDERR_FILENO, l);
	}
}
