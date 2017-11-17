/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 11:08:56 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/17 11:11:47 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"

static void	delete_other_paths(t_lemin *l)
{
	t_path	*prev;
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	l->path = l->path_begin;
	prev = l->path_begin;
	while (l->path)
	{
		if (l->path != l->best_path)
		{
			i = 0;
			while (l->best_path->path[i] != l->room_end && flag == 0)
			{
				j = 0;
				while (l->path->path[j] != l->room_end && flag == 0)
				{
					if (l->best_path->path[i] == l->path->path[j])
						flag = 1;
					j++;
				}
				i++;
			}
		}
		if (flag == 1)
		{
			if (l->path == l->path_begin)
			{
				l->path = l->path->next;
				free(prev->path);
				free(prev);
				prev = l->path;
				l->path_begin = l->path;
				prev = l->path;
			}
			else
			{
				prev->next = l->path->next;
				free(l->path->path);
				free(l->path);
				l->path = prev;
				prev = l->path;
				l->path = l->path->next;
			}
			flag = 0;
		}
		else
		{
			prev = l->path;
			l->path = l->path->next;
		}
	}
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
		if (l->path == l->path_begin)
			l->path_begin = l->path->next;
		l->solution->next = NULL;
	}
}
static void	find_best_path(t_lemin *l)
{
	l->path = l->path_begin;
	int	nb_path;
	int	nbr_coups;

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

static void calculate_different_paths(t_lemin *l)
{
	int	i;
	int	j;
	int	flag;
	t_path	*next;

	i = 0;
	j = 0;
	flag = 0;
	next = NULL;
	l->path = l->path_begin;
	next = l->path;
	while (l->path)
	{
		while (next->next)
		{
			next = next->next;
			i = 0;
			while (l->path->path[i] != l->room_end && flag == 0)
			{
				j = 0;
				while (next->path[j] != l->room_end && flag == 0)
				{
					if (l->path->path[i] == next->path[j])
						flag = 1;
					j++;
				}
				i++;
			}
			if (flag == 0)
			{
				l->path->different_path += 1;
				int nbr_coups_min = l->path->nbr_coups + next->nbr_coups;
				if (l->path->nbr_coups_min == 0 || l->path->nbr_coups_min < nbr_coups_min)
					l->path->nbr_coups_min = nbr_coups_min;
			}
			flag = 0;
		}
		l->path = l->path->next;
		next = l->path;
	}
}



void	resolve(t_lemin *l)
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
