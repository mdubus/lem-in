/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_create_ant_result.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:02:02 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/10 18:23:02 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	create_tab_result(t_lemin *l)
{
	int		i;
	t_path	*temp;

	i = 0;
	temp = NULL;
	l->result = (t_room **)malloc(sizeof(t_room*) *
			(unsigned long)(l->nb_path_final + 1));
	if (!l->result)
	{
		while (l->solution)
		{
			temp = l->solution;
			l->solution = l->solution->next;
			free(temp->path);
			free(temp);
		}
		free_at_end(l);
	}
	while (i <= l->nb_path_final)
		l->result[i++] = NULL;
}

static void	delete_solution(t_lemin *l)
{
	t_path	*temp;

	temp = NULL;
	l->solution = l->solution_begin;
	while (l->solution)
	{
		temp = l->solution;
		l->solution = l->solution->next;
		ft_memdel((void**)&temp->path);
		ft_memdel((void**)&temp);
	}
}

static void	order_result(t_lemin *l)
{
	t_room	*temp;
	int		i;

	temp = NULL;
	i = 0;
	while (i + 1 < l->nb_path_final)
	{
		if (l->result[i + 1]->length < l->result[i]->length)
		{
			temp = l->result[i + 1];
			l->result[i + 1] = l->result[i];
			l->result[i] = temp;
		}
		i++;
	}
}

static void	stock_path(t_lemin *l, t_room **path, int *j)
{
	while (*j >= 0)
	{
		(*path)->length = l->solution->nbr;
		(*path)->id = l->solution->path[*j];
		(*path)->ant = 0;
		(*path)->next = (t_room*)malloc(sizeof(t_room));
		(*path) = (*path)->next;
		(*j)--;
	}
	(*path)->id = l->room_start;
	(*path)->ant = l->nb_ants;
	(*path)->next = NULL;
	l->solution = l->solution->next;
}

void		create_ant_result(t_lemin *l)
{
	int		i;
	int		j;
	t_room	*path;

	i = 0;
	path = NULL;
	create_tab_result(l);
	l->solution = l->solution_begin;
	while (l->solution)
	{
		j = 0;
		path = (t_room*)malloc(sizeof(t_room));
		l->result[i] = path;
		while (l->solution->path[j] != l->room_end)
			j++;
		stock_path(l, &path, &j);
		i++;
	}
	delete_solution(l);
	order_result(l);
}
