/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_count_nb_paths.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:12:51 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/08 11:57:02 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static int	resolve_nb_paths(t_lemin *l, int *nb, int room)
{
	int	i;

	i = 1;
	while (i <= l->nb_rooms)
	{
		if (l->pipes[room][i] == 1)
		{
			if (i == l->room_end)
			{
				l->pipes[room][i] = 1;
				l->pipes[i][room] = 1;
			update_sum_tab(l);
				(*nb)++;
				ft_putnbr(i);
				ft_putchar(' ');
				return (0);
			}
			else if (i == l->room_start || l->sum[i] == 0)
			{
				l->pipes[room][i] = 1;
				l->pipes[i][room] = 1;
			update_sum_tab(l);
				ft_putnbr(i);
				ft_putchar(' ');

				return (1);
			}
			l->pipes[room][i] = 0;
			l->pipes[i][room] = 0;
			update_sum_tab(l);

			resolve_nb_paths(l, nb, i);
			l->pipes[room][i] = 1;
			l->pipes[i][room] = 1;
			update_sum_tab(l);
		}
				ft_putnbr(i);
				ft_putchar(' ');
		i++;
	}
	return (0);
}

void	count_nb_paths(t_lemin *l)
{
	resolve_nb_paths(l, &l->nb_path, l->room_start);
	printf("nombre de chemins = %d\n\n", l->nb_path);
	if (l->nb_path == 0)
	{
		free(l->sum);
		ft_memdel((void**)&l->string_file);
		ft_free_tab_char(&l->file);
		ft_free_tab_char(&l->eq);
		ft_free_tab_int(&l->pipes);
		free_lst_name(l);
		error_lem_in(&ft_putendl_fd,
				"\033[091mAucun chemin possible\033[0m",
				STDERR_FILENO);
	}
}
