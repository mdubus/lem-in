/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_remove_useless_paths.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 17:13:44 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/12 14:30:15 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	cut_paths(t_lemin *l, int room, int *level)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < l->nb_rooms)
	{
		if (l->pipes[room][i] == 1)
		{
			j = i + 1;
			while (j < l->nb_rooms)
			{
				if (l->pipes[room][j] == 1)
				{
					if (l->pipes[i][j] == 1 && level[room] != level[i] &&
							i != l->room_start && i != l->room_end &&
							j != l->room_start && j != l->room_end)
					{
						l->pipes[i][j] = 0;
						l->pipes[j][i] = 0;
					}
				}
				j++;
			}
		}
		i++;
	}
}

void	bfs(t_lemin *l, int room_start)
{
	int		k;
	int		i;
	int		end;
	t_queue	*queue;
	t_queue	*begin;

	i = 0;
	k = 0;
	end = 0;
	queue = NULL;
	l->visited = (bool*)malloc(sizeof(bool) * (unsigned long)l->nb_rooms);
	if (!l->visited)
	{
		free(l->sum);
		ft_memdel((void**)&l->string_file);
		ft_free_double_tab((void**)l->file);
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		free_lst_name(l);
	}
	l->level = (int*)malloc(sizeof(int) * (unsigned long)l->nb_rooms);
	if (!l->level)
	{
		free(l->sum);
		ft_memdel((void**)&l->string_file);
		ft_free_double_tab((void**)l->file);
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		free_lst_name(l);

	}
	while (i < l->nb_rooms)
	{
		l->level[i] = -1;
		l->visited[i++] = 0;
	}
	if (queue == NULL)
		queue = (t_queue*)malloc(sizeof(t_queue));
	if (!queue)
	{
		free(l->sum);
		ft_memdel((void**)&l->string_file);
		ft_free_double_tab((void**)l->file);
		ft_free_double_tab((void**)l->eq);
		ft_free_double_tab((void**)l->pipes);
		free_lst_name(l);

	}
	queue->id = room_start;
	queue->next = NULL;
	l->level[room_start] = k++;
	begin = queue;
	end = (room_start == l->room_start) ? l->room_end : l->room_start;
	while (begin && begin->id != end)
	{
		l->visited[begin->id] = 1;
		cut_paths(l, begin->id, l->level);
		int	j;
		t_queue	*temp;

		j = 0;
		temp = NULL;
		while (j < l->nb_rooms)
		{
			if (l->pipes[begin->id][j] == 1 && l->visited[j] == 0)
			{
				queue->next = (t_queue*)malloc(sizeof(t_queue));
				queue = queue->next;
				queue->next = NULL;
				queue->id = j;
				l->visited[queue->id] = 1;
				l->level[queue->id] = k;
			}
			j++;
		}
		temp = begin;
		if (begin->next)
		{
			begin = begin->next;
		}
		free(temp);
		if (l->level[begin->id] == k)
			k++;
	}
	free(l->visited);
	free(l->level);
	free(begin);
}
