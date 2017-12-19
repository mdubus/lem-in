/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:14:46 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:14:48 by mdubus           ###   ########.fr       */
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

void	free_pipes(t_lemin *l, char *str)
{
	free(l->string_file);
	ft_free_double_tab((void**)l->f);
	free_lst_name(l);
	ft_free_double_tab((void**)l->eq);
	ft_free_double_tab((void**)l->pipes);
	error_lem_in(ft_putendl_fd, str, STDERR_FILENO, l);
}

void	free_check_if_room(t_lemin *l, char *str)
{
	free(l->string_file);
	ft_free_double_tab((void**)l->f);
	free_lst_name(l);
	error_lem_in(ft_putendl_fd, str, STDERR_FILENO, l);
}
