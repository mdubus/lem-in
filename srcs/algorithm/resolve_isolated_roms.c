/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_isolated_roms.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 17:13:44 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/12 14:30:15 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
 ** Search for isolated rooms and suppress their pipes
 */

void		free_all(t_lemin *l)__attribute__((noreturn));
void		free_all(t_lemin *l)
{
	ft_memdel((void**)&l->string_file);
	ft_free_double_tab((void**)l->file);
	ft_free_double_tab((void**)l->eq);
	ft_free_double_tab((void**)l->pipes);
	free_lst_name(l);
	error_lem_in(&ft_putendl_fd,
			"\033[091mErreur lors d'une allocation memoire\033[0m",
			STDERR_FILENO, l);
}

void		update_sum_tab(t_lemin *l)
{
	int	total;
	int	i;
	int	j;

	total = 0;
	i = 0;
	j = 0;
	while (i < l->nb_rooms)
	{
		while (j < l->nb_rooms)
			total += l->pipes[i][j++];
		l->sum[i] = total;
		total = 0;
		j = 0;
		i++;
	}
}

void	create_sum_tab(t_lemin *l)
{
	l->sum = (int *)malloc(sizeof(int) * (unsigned int)(l->nb_rooms));
	if (l->sum == NULL)
		free_all(l);
}

void		check_for_isolated_rooms(t_lemin *l)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (i < l->nb_rooms)
	{
		if (i != l->room_start && i != l->room_end && l->sum[i] == 1)
		{
			while (j < l->nb_rooms)
			{
				if (l->pipes[i][j] == 1)
				{
					l->pipes[i][j] = 0;
					l->pipes[j][i] = 0;
					l->sum[i]--;
					l->sum[j]--;
					check_for_isolated_rooms(l);
				}
				j++;
			}
		}
		j = 0;
		i++;
	}
}
