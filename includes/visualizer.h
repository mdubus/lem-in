/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:01:51 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/09 17:28:32 by mdubus           ###   ########.fr       */
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
# define HEIGHT_W	1000


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
	SDL_Renderer		*screen;
	SDL_Texture			*background;
	SDL_Texture			*ant_img;
	SDL_Texture			*texture;
	SDL_Texture			*snorlax;
	SDL_Texture			*lava;
	SDL_Surface			*surf;
	SDL_Texture			*all;
	SDL_Rect			coor;
	TTF_Font			*typo;
	SDL_Event			event;
	SDL_Color			white;
	SDL_Color			purple;
	SDL_Color			pink;
	struct s_room_visu	*begin;
	struct s_room_visu	*first;
	struct s_room_visu	*next;
	struct s_turn		*turn_begin;
	struct s_turn		*turn;
	struct s_ant		*ant;
	struct s_ant		*ant_begin;
	char				*string_file;
	char				**file;
	int					width_room;
	int					height_room;
	int					startx;
	int					starty;
	int					endx;
	int					endy;
	int					begin_roomx;
	int					begin_roomy;
	int					end_roomx;
	int					end_roomy;
	int					end_room_id;
	int					ant_speed;
	int					nb_ant_start;
	int					nb_ant_end;
	int					ant_end;
	bool				loop;
	bool				flag_move_right;
	bool				flag_move_left;
	bool	init_sdl;
	bool	init_img;
	bool	init_ttf;
	bool	init_window;
	bool	init_screen;
	bool	init_typo;
	bool	init_background;
	bool	init_ant;
	bool	init_snorlax;
	bool	init_lava;
	bool	init_all;
	bool	ants_stocked;
	bool	loop_moving;
}						t_visu;

typedef struct	s_turn
{
	int					*turn;
	struct s_turn		*next;
	struct s_turn		*prev;
}						t_turn;

typedef struct	s_rect
{
	int			x;
	int			y;
	int			width;
	int			height;
	int			thick;
}				t_rect;

typedef struct	s_ant
{
	int				prevx;
	int				prevy;
	int				nextx;
	int				nexty;
	int				id;
	struct s_ant	*next;
}					t_ant;


SDL_Color	init_color(int r, int g, int b, int a);

void	init_struct(t_visu *v);
void	init_sdl(t_lemin *l, t_visu *v);
void	init_window_and_surface(t_visu *v);
void	free_rooms(t_visu *v);
void	put_on_screen_sdl(t_visu *v, SDL_Surface *surface, int x, int y);
void	put_all_on_screen_sdl(t_visu *v, SDL_Surface *surface);
void	 event_loop(t_visu *v, t_lemin *l);
int	visu_parsing_room_and_stock(t_lemin *l, t_room_visu **room, t_visu *v);
void	move_ant_left(t_lemin *l, t_visu *v);
void	move_ant_right(t_lemin *l, t_visu *v);
void	free_in_pipes(t_lemin *l, char *str, t_visu *v);
void	stock_turns(t_lemin *l, t_visu *v);
void	free_turns(t_visu *v);
void	free_all_and_quit(t_lemin *l, t_visu *v);
void	init_background(t_lemin *l, t_visu *v);
void	free_room_visu(t_lemin *l, char *str, t_visu *v);
void	free_parsing_visu(t_lemin *l, t_visu *v);
void	init_window(t_lemin *l, t_visu *v);
void	init_typo(t_lemin *l, t_visu *v);
void	init_ant(t_lemin *l, t_visu *v);
SDL_Rect	init_coor(int x, int y, int w, int h);
void	init_snorlax(t_lemin *l, t_visu *v);
void	init_lava(t_lemin *l, t_visu *v);
void	draw_pipes(t_lemin *l, t_visu *v);
void	draw_room(t_lemin *l, t_visu *v, t_room_visu *room);
void	draw_room_name(t_lemin *l, t_visu *v, t_room_visu *room);
void	draw_start_end_name(t_lemin *l, t_visu *v);
void	draw_arrows(t_lemin *l, t_visu *v);
void	free_ants(t_visu *v);
void	free_all_msg(t_lemin *l, t_visu *v, char *str);
void	draw_anthill(t_lemin *l, t_visu *v);
void	stock_ants(t_lemin *l, t_visu *v);
void	parsing_visu(t_lemin *l, t_visu *v, t_room_visu *room);


void	print_turns(t_lemin *l, t_visu *v);
void	print_rooms(t_visu *v);

#endif
