/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:01:51 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/15 16:52:27 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include <OpenGL/gl3.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <SDL.h>
# include <SDL_video.h>
# include <stdbool.h>
# include <SDL_ttf.h>
#include <SDL_image.h>
# include <SDL_keycode.h>
# include "lem_in.h"

# define CLOSE 27
# define LEFT 1073741904
# define RIGHT 1073741903

typedef struct	s_visu
{
	SDL_Window	*window;
	SDL_Surface	*surf;
	TTF_Font	*police;
	SDL_Event	event;
	SDL_Color	white;
	SDL_Color	purple;
	SDL_Color	pink;
	bool		loop;
	int			width_w;
	int			height_w;
}				t_visu;

#endif
