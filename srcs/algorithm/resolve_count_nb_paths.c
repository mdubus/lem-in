/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_count_nb_paths.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:12:51 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/10 20:50:11 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	print_possible_paths(t_lemin *l)
{
	int j = 0;
	while (j < l->nb_rooms)
	{
		ft_putnbr(l->lookup[j++]);
		ft_putchar(' ');
	}
}

static int	resolve_nb_paths(t_lemin *l, int room, int *j)
{
	int	i;

	i = 0;
	while (i < l->nb_rooms)
	{
		if (l->pipes[room][i] == 1)
		{
	//		ft_putnbr(i);
	//		ft_putchar('\n');
			(*j)++;
			if (room != l->room_start)
				l->lookup[room] = *j;
			l->pipes[room][i] = 0;
			l->pipes[i][room] = 0;
			if (i == l->room_end)
			{
				print_possible_paths(l);
				ft_putchar('\n');
	//			ft_putendl("end");
				(l->nb_path)++;
				l->pipes[room][i] = 1;
				l->pipes[i][room] = 1;
				(*j)--;
				l->lookup[room] = 0;
			}
			else if (l->lookup[i] > 0)
			{
	//			printf("%d already visited\n", room);
				(*j)--;
				l->lookup[room] = 0;
				l->pipes[room][i] = 1;
				l->pipes[i][room] = 1;
			}
			else
			{
				resolve_nb_paths(l, i, j);
				l->pipes[room][i] = 1;
				l->pipes[i][room] = 1;
				(*j)--;
				l->lookup[room] = 0;
			}
		}
		i++;
	}
	return (0);
}

void	count_nb_paths(t_lemin *l)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	l->lookup = (int *)malloc(sizeof(int) * (unsigned long)(l->nb_rooms));
	while (i < l->nb_rooms)
		l->lookup[i++] = 0;
	resolve_nb_paths(l, l->room_start, &j);
	printf("\n\nnombre de chemins = %d\n\n", l->nb_path);
	if (l->nb_path == 0)
	{
		free(l->sum);
		ft_memdel((void**)&l->string_file);
		ft_free_double_tab((void**)l->file);
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		free_lst_name(l);
		error_lem_in(&ft_putendl_fd,
				"\033[091mAucun chemin possible\033[0m",
				STDERR_FILENO);
	}
	free(l->lookup);
}
