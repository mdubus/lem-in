/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:32:48 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/10 13:04:01 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	ft_free_tab_bool(bool **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}

void	free_queue(t_queue *lst)
{
	t_queue	*temp;

	temp = NULL;
	while (lst)
	{
		temp = lst;
		lst = lst->next;
		free(temp);
	}
}

void	free_pipes_and_sum(t_lemin *l, char *str)
{
	free(l->sum);
	free(l->string_file);
	ft_free_double_tab((void**)l->f);
	free_lst_name(l);
	ft_free_double_tab((void**)l->eq);
	ft_free_double_tab((void**)l->pipes);
	error_lem_in(ft_putendl_fd, str, STDERR_FILENO, l);
}

void	free_at_end(t_lemin *l)
{
	free(l->sum);
	ft_memdel((void**)&l->string_file);
	ft_free_double_tab((void**)l->f);
	ft_free_double_tab((void**)l->eq);
	ft_free_double_tab((void**)l->pipes);
	l->solution = l->solution_begin;
	free(l->sorted);
	free_lst_name(l);
}

void	free_result(t_lemin *l)
{
	t_room	*path;
	t_room	*temp;
	int		i;

	i = 0;
	path = NULL;
	temp = NULL;
	while (l->result[i] != NULL)
	{
		path = l->result[i];
		while (path)
		{
			temp = path;
			path = path->next;
			free(temp);
		}
		i++;
	}
	free(l->result);
}
