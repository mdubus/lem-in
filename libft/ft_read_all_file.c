/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_all_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:58:19 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/10 13:05:59 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static void	concat(char **temp, char **line)
{
	if (*temp == NULL)
	{
		*temp = ft_strdup(*line);
		free(*line);
	}
	else
	{
		if (*line != NULL)
			*temp = ft_strjoin_proper(*temp, 1, *line, 1);
	}
}

char		*ft_read_all_file(int fd)
{
	int		ret;
	char	*line;
	char	*temp;
	t_dlist	*list;

	ret = 1;
	line = NULL;
	temp = NULL;
	list = NULL;
	while (ret == 1)
	{
		ret = get_next_line_backslash(fd, &line, list);
		if (ret == 1 || ret == 0)
			concat(&temp, &line);
		else
			ft_memdel((void**)&temp);
	}
	free(list);
	return (temp);
}
