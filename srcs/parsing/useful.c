/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:17:49 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:18:52 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	error_lem_in(void (*function)(const char *, int fd),
		const char *str, int fd, t_lemin *l)
{
	if (l->debug == 1)
	{
		(*function)(str, fd);
		exit(1);
	}
	else
	{
		ft_putendl_fd("ERROR", STDOUT_FILENO);
		exit(1);
	}
}
