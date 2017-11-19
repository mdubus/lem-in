/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 11:18:14 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/19 11:18:59 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

SDL_Color	init_color(int r, int g, int b, int a)
{
	SDL_Color	color;

	color.r = (Uint8)r;
	color.g = (Uint8)g;
	color.b = (Uint8)b;
	color.a = (Uint8)a;
	return (color);
}
