/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 14:33:37 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/18 17:22:19 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	free_lst_name(t_lemin *l)
{
	t_room	*temp;

	temp = NULL;
	while (l->begin)
	{
		temp = l->begin;
		l->begin = l->begin->next;
		ft_memdel((void**)&temp->name);
		ft_memdel((void**)&temp);
	}
}

void	ft_free_tab_bool(bool **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}

void	error_in_bfs(t_lemin *l)
{
	free(l->sum);
	ft_memdel((void**)&l->string_file);
	ft_free_double_tab((void**)l->f);
	ft_free_double_tab((void**)l->eq);
	ft_free_double_tab((void**)l->pipes);
	free_lst_name(l);
	error_lem_in(ft_putendl_fd,
			"\033[091mErreur lors d'une allocation\033[0m",
			STDERR_FILENO, l);
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
