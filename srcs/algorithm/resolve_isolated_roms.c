/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_isolated_roms.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 17:13:44 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/06 17:22:16 by mdubus           ###   ########.fr       */
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
	ft_free_tab_char(&l->file);
	ft_free_tab_char(&l->eq);
	free_lst_name(l);
	ft_free_tab_int(&l->pipes);
	error_lem_in(&ft_putendl_fd,
			"\033[091mErreur lors d'une allocation memoire\033[0m",
			STDERR_FILENO);
}

static int	*create_sum_tab(t_lemin *l)
{
	int	*sum;
	int	i;
	int	total;
	int	j;

	sum = NULL;
	i = 1;
	total = 0;
	j = 1;
	sum = (int *)malloc(sizeof(int) * (unsigned int)(l->nb_rooms + 1));
	if (sum == NULL)
		free_all(l);
	while (i <= l->nb_rooms)
	{
		while (j <= l->nb_rooms)
			total += l->pipes[i][j++];
		sum[i] = total;
		total = 0;
		j = 1;
		i++;
	}
	return (sum);
}

void		check_for_isolated_rooms(t_lemin *l)
{
	int	*sum;
	int	i;
	int j;

	i = 1;
	j = 1;
	sum = create_sum_tab(l);
	while (i <= l->nb_rooms)
	{
		if (i != l->room_start && i != l->room_end && sum[i] == 1)
		{
			while (j <= l->nb_rooms && l->pipes[i][j] != 1)
				j++;
			l->pipes[i][j] = 0;
			l->pipes[j][i] = 0;
		}
		j = 1;
		i++;
	}
	free(sum);
}
