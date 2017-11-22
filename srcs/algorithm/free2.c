/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:32:48 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/22 15:33:21 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	free_check_if_room(t_lemin *l, char *str)
{
	free(l->string_file);
	ft_free_double_tab((void**)l->f);
	free_lst_name(l);
	error_lem_in(ft_putendl_fd, str, STDERR_FILENO, l);
}

void	free_pipes(t_lemin *l, char *str)
{
	free(l->string_file);
	ft_free_double_tab((void**)l->f);
	free_lst_name(l);
	ft_free_double_tab((void**)l->eq);
	ft_free_double_tab((void**)l->pipes);
	error_lem_in(ft_putendl_fd, str, STDERR_FILENO, l);
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
