/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:36:25 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/01 19:00:53 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

#ifdef DEBUG

void	error_lem_in(void (*function)(const char *, int fd),
		const char *str, int fd)
{
	(*function)(str, fd);
	exit(1);
}

#else

void	error_lem_in(void (*function)(const char *, int fd),
		const char *str, int fd)
{
	(void)function;
	(void)str;
	(void)fd;
	ft_putendl_fd("ERROR", STDOUT_FILENO);
	exit(1);
}

#endif
