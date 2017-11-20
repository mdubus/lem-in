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
		//		SDL_FreeSurface(surface);
		ft_putstr("Error put_on_screen_sdl : ");
		SDL_GetError();
	}
	//	SDL_FreeSurface(surface);
}


void	put_all_on_screen_sdl(t_visu *v, SDL_Surface *surface)
{
	if (SDL_BlitSurface(surface, NULL, v->surf, NULL) < 0)
	{
		//		SDL_FreeSurface(surface);
		ft_putstr("Error put_all_on_screen_sdl : ");
		SDL_GetError();
	}
	//	SDL_FreeSurface(surface);
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

static void	move_ant(t_visu *v)
{
	while (v->x <= 600 && v->y <= 500)
	{
		v->temps_actuel = SDL_GetTicks();
		if (v->temps_actuel - v->temps_precedent > SKIP_TICKS)
		{
			//		SDL_FillRect(v->surf, NULL, SDL_MapRGB(v->surf->format, 0, 0, 0));
			//		put_all_on_screen_sdl(v, v->background);
			v->x += 4;
			v->y += 4;
			refresh_background(v, v->background, v->x, v->y);
			put_on_screen_sdl(v, v->ant, v->x, v->y);
			v->temps_precedent = v->temps_actuel;
			SDL_UpdateWindowSurface(v->window);
		}
	}
}

static void event_loop(t_visu *v)
{
	while (v->loop)
	{
		while (SDL_PollEvent(&(v->event)))
		{
			if (v->event.type == SDL_QUIT)
				v->loop = false;
			else if (v->event.type == SDL_KEYDOWN)
			{
				if (v->event.key.keysym.sym == CLOSE)
					v->loop = false;
				else if (v->event.key.keysym.sym == RIGHT)
				{
					move_ant(v);
					//	refresh_background(v, v->background, v->x, 400);
				}
			}
		}
	}
	if (v->loop == false)
	{
		SDL_DestroyWindow(v->window);
		IMG_Quit();
		SDL_Quit();
	}
}




static void	init_put_background(t_visu *v)
{
	SDL_Surface	*image;

	image = NULL;
	image = IMG_Load("srcs/visualizer/img/background.png");
	if (!image)
		ft_putendl("impossible de load l'image");
	put_on_screen_sdl(v, image, 0, 0);
	SDL_UpdateWindowSurface(v->window);
}

int	main(void)
{
	t_visu v;

	init_struct(&v);

	init_SDL(&v);
	init_window_and_surface(&v);
	init_put_background(&v);


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
