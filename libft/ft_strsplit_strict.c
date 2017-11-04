/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_strict.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:48:46 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/03 14:27:56 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static size_t	nb_words(char *str, char c)
{
	size_t	nb;
	int		i;

	nb = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			nb++;
		}
		i++;
	}
	return (nb + 1);
}

char			**ft_strsplit_strict(char *str, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;
	size_t	k;

	tab = NULL;
	i = 0;
	j = 0;
	k = 0;
	if (!str || str == NULL)
		return (NULL);
	if ((tab = (char **)malloc(sizeof(char*) * (nb_words(str, c) + 1))) == NULL)
		return (NULL);
	while (str[i++] != '\0')
	{
		if (str[i] == c)
		{
			tab[k++] = ft_strsub(str, (unsigned int)j, i - j);
			j = i + 1;
		}
	}
	if (str[i - 2] != '\n')
		tab[k++] = ft_strsub(str, (unsigned int)j, i - j);
	tab[k] = NULL;
	return (tab);
}
