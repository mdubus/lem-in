/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:00:49 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/20 16:45:08 by mdubus           ###   ########.fr       */
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






int	main(void)
{
	t_visu v;

	init_struct(&v);

	init_SDL(&v);
	init_window_and_surface(&v);

	put_all_on_screen_sdl(&v, v.background);
	put_on_screen_sdl(&v, v.ant, v.x, 400);
	SDL_UpdateWindowSurface(v.window);

	//	refresh_background(&v, v.background, v.x, 400);
	//	SDL_UpdateWindowSurface(v.window);



	/*	char	*line = NULL;
		int ret = 0;
		while ((ret = get_next_line_backslash(STDIN_FILENO, &line)) > 0)
		{
		ft_putstr(line);
		free(line);
		}
		*/

	event_loop(&v);

}
