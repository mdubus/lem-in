/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_plus_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 13:33:12 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/01 13:34:20 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup_plus_char(const char *s1, char c)
{
	char	*duplicate;
	int		strlen;
	int		j;

	strlen = ft_strlen_secure(s1);
	j = 0;
	duplicate = (char *)malloc(((unsigned long)strlen + 2) * sizeof(char));
	if (duplicate == NULL)
		return (NULL);
	while (s1[j] != '\0')
	{
		duplicate[j] = s1[j];
		j++;
	}
	duplicate[j] = c;
	duplicate[j + 1] = '\0';
	return (duplicate);
}
