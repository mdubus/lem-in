/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:00:49 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/18 19:15:06 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/visualizer.h"


static SDL_Color	init_color(int r, int g, int b, int a)
{
	SDL_Color	color;

	color.r = (Uint8)r;
	color.g = (Uint8)g;
	color.b = (Uint8)b;
	color.a = (Uint8)a;
	return (color);
}

static void init_struct(t_visu *v)
{
	v->window = NULL;
	v->surf = NULL;
	v->police = NULL;
	v->white = init_color(255, 255, 255, 255);
	v->purple = init_color(215, 149, 242, 255);
	v->pink = init_color(237, 101, 162, 255);
	v->loop = true;
	v->width_w = 1600;
	v->height_w = 1000;
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

static void	put_on_screen_sdl(t_visu *v, SDL_Surface *surface, int x, int y)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	if (SDL_BlitSurface(surface, NULL, v->surf, &rect) < 0)
	{
		SDL_FreeSurface(surface);
		ft_putstr("Error on TTF_RenderTextBlended : ");
		SDL_GetError();
	}
	SDL_FreeSurface(surface);
}

static void	init_SDL()
{
	int	flags;
	int	initted;

	flags = 0;
	initted = 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_putstr("Unable to initialize SDL : ");
		SDL_GetError();
	}
	flags = IMG_INIT_JPG | IMG_INIT_PNG;
	initted = IMG_Init(flags);
	if ((initted&flags) != flags)
	{
		ft_putstr("Failed to init required jpg and png support\n");
		IMG_GetError();
		SDL_Quit();
		exit(1);
	}
}

static void	init_window_and_surface(t_visu *v)
{
	if ((v->window = SDL_CreateWindow("Lem-in", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, v->width_w, v->height_w,
					SDL_WINDOW_SHOWN)) == NULL)
	{
		ft_putstr("Unable to initialize window : ");
		SDL_GetError();
	}
	if ((v->surf = SDL_GetWindowSurface(v->window)) == NULL)
	{
		ft_putstr("Unable to initialize surface : ");
		SDL_GetError();
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

	init_SDL();
	init_window_and_surface(&v);
	init_put_background(&v);

	char	*line = NULL;
	int ret = 0;
	while ((ret = get_next_line_backslash(STDIN_FILENO, &line)) > 0)
	{
		ft_putstr(line);
		free(line);
	}


	event_loop(&v);

}
