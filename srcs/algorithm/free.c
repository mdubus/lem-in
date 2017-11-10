/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 14:33:37 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/10 18:08:12 by mdubus           ###   ########.fr       */
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

void	ft_free_tab_bool(bool **tab);
void	ft_free_tab_bool(bool **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}
