/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:36:25 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/15 15:24:10 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
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
