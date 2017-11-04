/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_all_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:58:19 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/04 12:21:20 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

#include <stdio.h>

char	*ft_read_all_file(int fd)
{
	int		ret;
	char	*line;
	char	*temp;

	ret = 1;
	line = NULL;
	temp = NULL;
	while (ret == 1)
	{
		ret = get_next_line_backslash(fd, &line);
		if (ret == 1 || ret == 0)
		{
			if (temp == NULL)
			{
				temp = ft_strdup(line);
				free(line);
			}
			else
			{
				if (line != NULL)
					temp = ft_strjoin_proper(temp, 1, line, 1);
			}
		}
		else
		{
			ft_memdel((void**)&temp);
	//		free(line);
		}
	}
	return (temp);
}
