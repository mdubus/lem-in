/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:24:26 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/18 17:34:43 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic error "-Weverything"
#include "../../includes/lem_in.h"
/*
   static void	print_ants(t_lemin *l)
   {
   int	i;

   i = 0;
   l->solution = l->solution_begin;
   while (l->solution)
   {
   l->nb_path_final++;
   l->solution = l->solution->next;
   }
   l->solution = l->solution_begin;
   while (i < l->nb_ants)
   {
   ft_putchar('L');
   ft_putchar('x');
   ft_putchar('-');
   ft_putchar('x');
   ft_putchar(' ');
   if ((i + 1) % l->nb_path_final == 0)
   ft_putchar('\n');
   i++;
   }
   ft_putchar('\n');
   }


   typedef struct		s_room
   {
   int				id;
   int				ant;
   char			*name;
   struct s_room	*next;
   }					t_room;

*/

static void	create_tab_result(t_lemin *l)
{
	int	i;

	i = 0;
	l->result = (t_room **)malloc(sizeof(t_room*) * (unsigned long)(l->nb_path_final + 1));
	while (i <= l->nb_path_final)
		l->result[i++] = NULL;
}

static void	delete_solution(t_lemin *l)
{
	t_path	*temp;

	temp = NULL;
	l->solution = l->solution_begin;
	while (l->solution)
	{
		temp = l->solution;
		l->solution = l->solution->next;
		ft_memdel((void**)&temp->path);
		ft_memdel((void**)&temp);
	}
}

static void	create_ant_result(t_lemin *l)
{
	int	i;
	int	j;

	i = 0;
	create_tab_result(l);
	l->solution = l->solution_begin;
	while (l->solution)
	{
		t_room	*path;
		j = 0;
		path = (t_room*)malloc(sizeof(t_room));
		l->result[i] = path;
		while (l->solution->path[j] != l->room_end)
			j++;
		while (j >= 0)
		{
			path->length = l->solution->nbr;
			path->id = l->solution->path[j];
			path->next = (t_room*)malloc(sizeof(t_room));
			path = path->next;
			j--;
		}
		path->id = l->room_start;
		path->next = NULL;
		l->solution = l->solution->next;
		i++;
	}
	delete_solution(l);
}

int	main(int argc, char **argv)
{
	t_lemin	l;


	init_struct_lemin(&l);
	init_arguments(argc, argv, &l);
	parsing(&l);

	remove_useless_paths(&l);
	if (l.debug == 1)
	{
		print_resume(&l);
		print_equivalence_tab(&l);
		ft_print_tab_pipes(&l);
		print_possible_paths(&l);
	}


	resolve(&l);

	if (l.debug == 1)
	{
		print_result(&l);
		ft_putendl("\033[94m---------- Resultat ----------\n\033[0m");
	}
	ft_putendl(l.string_file);

	create_ant_result(&l);


	int	i;
	t_room	*temp;

	i = 0;
	temp = NULL;
	while (l.result[i] != NULL)
	{
		temp = l.result[i];
		while (temp)
		{
			printf("%d\n", temp->id);
			temp = temp->next;
		}
		i++;
		ft_putchar('\n');
	}

// l->result->length contient la longueur du chemin. 
// Trier pour que le plus court apparaisse en premier dans le tableau
// Et soit donc execute en premier



	//	print_ants(&l);

	free_at_end(&l);
	return (0);
}
