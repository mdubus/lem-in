/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:00:49 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/24 15:37:20 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualizer.h"

void	put_on_screen_sdl(t_visu *v, SDL_Surface *surface, int x, int y)
{
	SDL_Rect	coor;

	coor.x = x;
	coor.y = y;
	if (SDL_BlitSurface(surface, NULL, v->surf, &coor) < 0)
	{
		ft_putstr("Error put_on_screen_sdl : ");
		SDL_GetError();
	}
}


void	put_all_on_screen_sdl(t_visu *v, SDL_Surface *surface)
{
	SDL_Rect	coor;

	coor.x = 0;
	coor.y = 0;
	coor.w = v->width_w;
	coor.h = v->height_w;
	if (SDL_BlitSurface(surface, &coor, v->surf, NULL) < 0)
	{
		ft_putstr("Error put_all_on_screen_sdl : ");
		SDL_GetError();
	}
}

static void	refresh_background(t_visu *v, SDL_Surface *surface, int x, int y)
{
	SDL_Rect	coor;

	coor.x = x;
	coor.y = y;
	coor.w = v->ant->w;
	coor.h = v->ant->h;
	if (SDL_BlitSurface(surface, &coor, v->surf, &coor) < 0)
	{
		ft_putstr("Error on BlitSurface : ");
		SDL_GetError();
	}
}

void	move_ant(t_visu *v)
{
	v->temps_actuel = SDL_GetTicks();
	if (v->temps_actuel - v->temps_precedent > SKIP_TICKS)
	{
		refresh_background(v, v->background, v->x, v->y);
		v->x += v->ant_speed;
		v->y += v->ant_speed;
		put_on_screen_sdl(v, v->ant, v->x, v->y);
		v->temps_precedent = v->temps_actuel;
		SDL_UpdateWindowSurface(v->window);
	}
}

static void	create_turn(t_lemin *l, t_visu *v)
{
	if (!v->turn_begin)
	{
		v->turn = (t_turn*)malloc(sizeof(t_turn));
		if (!v->turn)
			free_in_pipes(l, "Error with malloc", v);
		v->turn_begin = v->turn;
	}
	else
	{
		v->turn->next = (t_turn*)malloc(sizeof(t_turn));
		if (!v->turn->next)
			free_in_pipes(l, "Error with malloc", v);
		v->turn = v->turn->next;
	}
}

static void	stock_turn(t_lemin *l, t_visu *v, char *str)
{
	char	**tab;
	int		i;
	int		ant;
	char	*room;
	t_room_visu	*room_visu;

	tab = NULL;
	i = 0;
	ant = 0;
	room = NULL;
	create_turn(l, v);
	v->turn->next = NULL;
	v->turn->turn = NULL;
	v->turn->turn = (int*)malloc(sizeof(int) * (l->nb_ants + 1));
	if (!v->turn->turn)
		free_in_pipes(l, "Error with malloc", v); //free aussi chaque maillon turn
	while (i <= l->nb_ants)
		v->turn->turn[i++] = -1;
	tab = ft_strsplit(str, ' ');
	if (!tab)
		free_in_pipes(l, "Error with malloc", v); //free aussi chaque maillon turn
	i = 0;
	if (ft_strchr(tab[i], '-') == 0)
		free_in_pipes(l, "Error with malloc", v); //free aussi chaque maillon turn
	while (tab[i])
	{
		ant = ft_atoi(&tab[i][1]);
		room = ft_strdup(ft_strchr(tab[i], '-') + 1);
		room_visu = v->begin;
		while (room_visu && (ft_strstr(room_visu->name, room) == 0))
			room_visu = room_visu->next;
		if (ft_strstr(room_visu->name, room) != 0)
		{
			v->turn->turn[ant] = room_visu->id;
		}
		i++;
	}
	free(room);
}

static void	stock_turns(t_lemin *l, t_visu *v)
{
	int	i;

	i = l->start + 1;
	if (l->f[i] && l->f[i][0] && l->f[i][0] == 'L')
	{
		while (l->f[i])
		{
			stock_turn(l, v, l->f[i]);
			i++;
		}
	}
	else
		free_in_pipes(l, "Error", v);
}

int	main(void)
{
	t_visu	v;
	t_lemin	l;
	t_room_visu	*room;

	init_struct_lemin(&l);
	get_file(&l);
	ft_putendl(l.string_file);
	parsing_ants_number(&l);
	if (visu_parsing_room_and_stock(&l, &room, &v) == 2)
		free_check_if_room(&l,
				"\033[091mErreur : La map est mal formatee\033[0m");
	visu_parsing_pipes(&l, &v);

	room = v.begin;
	while (room)
	{
		printf("%d : %s\n", room->id, room->name);
		printf("x = %d, y = %d\n", room->coorx, room->coory);
		printf("special = %d\n\n", room->special);
		room = room->next;
	}

	printf("*************************\n");
	stock_turns(&l, &v);

	t_turn	*turn;
	int		i;

	i = 0;
	turn = v.turn_begin;
	while (i <= l.nb_ants)
		ft_printf("%2d ", i++);
	ft_putendl("(ant)");
	i = 0;
	while (turn)
	{
		while (i <= l.nb_ants)
			ft_printf("%2d ", turn->turn[i++]);
		turn = turn->next;
		i = 0;
		ft_putchar('\n');
	}






	init_struct(&v);

	init_SDL(&v);
	init_window_and_surface(&v);









	put_all_on_screen_sdl(&v, v.background);
	put_on_screen_sdl(&v, v.ant, v.x, 400);
	SDL_UpdateWindowSurface(v.window);


	event_loop(&v, &l);

}
