/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:01:51 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/20 16:09:22 by mdubus           ###   ########.fr       */
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
# define PLUS 1073741911
# define MINUS 1073741910

# define FPS 60
# define SKIP_TICKS 1000 / FPS

typedef struct	s_visu
{
	SDL_Window	*window;
	SDL_Surface	*surf;
	SDL_Surface	*background;
	SDL_Surface	*ant;
	TTF_Font	*police;
	SDL_Event	event;
	SDL_Color	white;
	SDL_Color	purple;
	SDL_Color	pink;
	bool		loop;
	bool		flag_move;
	int			width_w;
	int			height_w;
	int			x;
	int			y;
	Uint16		delay;
	int			temps_actuel;
	int			temps_precedent;
	int			ant_speed;
}				t_visu;


SDL_Color	init_color(int r, int g, int b, int a);

void	init_struct(t_visu *v);
void	init_SDL(t_visu *v);
void	init_window_and_surface(t_visu *v);


void	put_on_screen_sdl(t_visu *v, SDL_Surface *surface, int x, int y);
void	put_all_on_screen_sdl(t_visu *v, SDL_Surface *surface);

void event_loop(t_visu *v);

void	move_ant(t_visu *v);




#endif
