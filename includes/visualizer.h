/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:01:51 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/29 18:13:49 by mdubus           ###   ########.fr       */
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
# include <SDL_image.h>
# include <SDL_keycode.h>
# include "lem_in.h"

# define CLOSE 27
# define LEFT 1073741904
# define RIGHT 1073741903
# define PLUS 1073741911
# define MINUS 1073741910


# define FPS 60
# define SKIP_TICKS 1000 / FPS

# define START 1
# define END 2
# define SNORLAX 3
# define LAVA 4
# define WIDTH_W	1300
# define HEIGHT_W	800


typedef struct	s_room_visu
{
	int					x;// Coordonnees milieu en px
	int					y;
	int					special;
	int					id;
	char				*name;
	struct s_room_visu	*next;
}						t_room_visu;

typedef struct	s_visu
{
	SDL_Window			*window;
	SDL_Surface			*surf;
	SDL_Surface			*background;
	SDL_Surface			*ant;
	TTF_Font			*typo;
	SDL_Event			event;
	SDL_Color			white;
	SDL_Color			purple;
	SDL_Color			pink;
	struct s_room_visu	*begin;
	struct s_turn		*turn_begin;
	struct s_turn		*turn;
	char				*string_file;
	char				**file;
	int					width_room;
	int					height_room;
	int					x; // enlever
	int					y; // enlever
	int					temps_actuel;
	int					temps_precedent;
	int					ant_speed;
	bool				loop;
	bool				flag_move;
}						t_visu;

typedef struct	s_turn
{
	int					*turn;
	struct s_turn		*next;
}						t_turn;

typedef struct	s_rect
{
	int			x;
	int			y;
	int			width;
	int			height;
	int			thick;
}				t_rect;


SDL_Color	init_color(int r, int g, int b, int a);

void	init_struct(t_visu *v);
void	init_SDL(t_visu *v);
void	init_window_and_surface(t_visu *v);
void	free_rooms(t_visu *v);
void	put_on_screen_sdl(t_visu *v, SDL_Surface *surface, int x, int y);
void	put_all_on_screen_sdl(t_visu *v, SDL_Surface *surface);
void event_loop(t_visu *v, t_lemin *l);
int	visu_parsing_room_and_stock(t_lemin *l, t_room_visu **room, t_visu *v);
int	visu_parsing_pipes(t_lemin *l, t_visu *v);
void	move_ant(t_visu *v);
void	free_in_pipes(t_lemin *l, char *str, t_visu *v);
void	stock_turns(t_lemin *l, t_visu *v);
void	free_turns(t_visu *v);
void	free_all_and_quit(t_lemin *l, t_visu *v);
void	draw_room(t_lemin *l, t_visu *v, t_room_visu *room);
void	init_background(t_lemin *l, t_visu *v);


void	print_turns(t_lemin *l, t_visu *v);
void	print_rooms(t_visu *v);

#endif
