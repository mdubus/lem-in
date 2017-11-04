/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:24:26 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/04 20:06:59 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	init_struct_lemin(t_lemin *l);
void	init_struct_lemin(t_lemin *l)
{
	l->nb_ants = -1;
	l->nb_pipes = 0;
	l->nb_rooms = 0;
	l->flag_start = 0;
	l->flag_end = 0;
	l->id = 0;
	l->comments = 0;
	l->commands = 0;
	l->start = 0;
	l->pipes = NULL;
	l->string_file = NULL;
	l->room_start = NULL;
	l->room_end = NULL;
	l->file = NULL;
	l->room = NULL;
	l->begin = NULL;
}


void	free_check_if_room(t_lemin *l, char *str)
{
	free(l->string_file);
	ft_free_tab_char(&l->file);
	free_lst_name(l);
	error_lem_in(ft_putendl_fd, str, STDERR_FILENO);
}





int	main(void)
{
	t_lemin	l;

	init_struct_lemin(&l);
	get_file(&l);
	ft_putendl(l.string_file);

	parsing_ants_number(&l);
	if (parsing_room_and_stock(&l) == 2)
	{
			free_check_if_room(&l,
			"\033[091mErreur : La map est mal formatee\033[0m");
	}
	parsing_pipes_and_stock(&l);
	check_end_and_start(&l);




//	ft_print_tab_int(l.pipes, l.nb_rooms);
/*
	ft_putchar('\n');
	l.room = l.begin;
	printf("id | nom\n");
	while (l.room)
	{
		printf(" %d | %s\n", l.room->id, l.room->name);
		l.room = l.room->next;
	}
	l.room = l.begin;

	printf("\nstart = %s, end = %s\n", l.room_start, l.room_end);
*/
	ft_memdel((void**)&l.string_file);
	ft_free_tab_char(&l.file);
	free_lst_name(&l);
	ft_free_tab_int(&l.pipes);



	return (0);
}
