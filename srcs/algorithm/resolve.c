/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:13:36 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:13:37 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	put_it_in_solution(t_lemin *l, t_path *temp)
{
	if (l->solution == NULL)
	{
		l->solution = l->path;
		l->solution_begin = l->solution;
	}
	else
	{
		l->solution->next = l->path;
		l->solution = l->solution->next;
	}
	temp->next = l->path->next;
	l->nb_path_final++;
	if (l->path == l->path_begin)
		l->path_begin = l->path->next;
	l->solution->next = NULL;
}

static void	put_best_path_in_result(t_lemin *l)
{
	t_path	*temp;

	l->path = l->path_begin;
	temp = l->path;
	while (l->path && l->path != l->best_path)
	{
		temp = l->path;
		l->path = l->path->next;
	}
	if (l->path == l->best_path)
		put_it_in_solution(l, temp);
}

static void	find_best_path(t_lemin *l)
{
	int	nb_path;
	int	nbr_coups;

	l->path = l->path_begin;
	nb_path = l->path->different_path;
	nbr_coups = l->path->nbr_coups;
	l->best_path = l->path;
	while (l->path)
	{
		if (l->path->different_path > nb_path)
		{
			nb_path = l->path->different_path;
			l->best_path = l->path;
		}
		else if (l->path->different_path == nb_path)
		{
			if (l->path->nbr_coups < nbr_coups)
			{
				nbr_coups = l->path->nbr_coups;
				l->best_path = l->path;
			}
		}
		l->path = l->path->next;
	}
}

void		resolve(t_lemin *l)
{
	while (l->path_begin)
	{
		l->path = l->path_begin;
		while (l->path)
		{
			l->path->nbr_coups_min = 0;
			l->path->different_path = 0;
			l->path = l->path->next;
		}
		calculate_different_paths(l);
		find_best_path(l);
		delete_other_paths(l);
		put_best_path_in_result(l);
	}
}
