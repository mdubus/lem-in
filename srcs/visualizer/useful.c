/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <mdubus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:20:39 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/19 11:20:40 by mdubus           ###   ########.fr       */
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

SDL_Rect	init_coor(int x, int y, int w, int h)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}
