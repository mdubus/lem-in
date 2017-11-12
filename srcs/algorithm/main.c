/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:24:26 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/12 21:54:56 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	free_check_if_room(t_lemin *l, char *str)
{
	free(l->string_file);
	ft_free_double_tab((void**)l->file);
	free_lst_name(l);
	error_lem_in(ft_putendl_fd, str, STDERR_FILENO, l);
}



void	make_tab_equivalence(t_lemin *l);
void	make_tab_equivalence(t_lemin *l)
{
	l->eq = (char **)malloc(sizeof(char*) * (unsigned long)(l->nb_rooms + 1));
	if (l->eq == NULL)
		free_check_if_room(l,
				"\033[091mErreur lors d'une allocation memoire\033[0m");
	l->room = l->begin;
	while (l->room != NULL)
	{
		l->eq[l->room->id] = ft_strdup(l->room->name);
		l->room = l->room->next;
	}
	l->room = l->begin;
	l->eq[l->nb_rooms] = NULL;
}

void	print_sum_table(t_lemin *l);
void	print_sum_table(t_lemin *l)
{
	ft_putchar('\n');
	int i = 0;
	while (i < l->nb_rooms)
		printf("%d\n", l->sum[i++]);
}

static void	cut_paths(t_lemin *l, int room)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < l->nb_rooms)
	{
		if (l->pipes[room][i] == 1)
		{
			j = i + 1;
			while (j < l->nb_rooms)
			{
				if (l->pipes[room][j] == 1)
				{
					if (l->pipes[i][j] == 1)
					{
						l->pipes[i][j] = 0;
						l->pipes[j][i] = 0;
					}
				}
				j++;
			}
		}
		i++;
	}
}

static void	bfs(t_lemin *l)
{
	bool	*visited;
	int		i;
	t_queue	*queue;
	t_queue	*begin;

	visited = NULL;
	i = 0;
	queue = NULL;
	visited = (bool*)malloc(sizeof(bool) * (unsigned long)l->nb_rooms);
	while (i < l->nb_rooms)
		visited[i++] = 0;

	if (queue == NULL)
		queue = (t_queue*)malloc(sizeof(t_queue));
	queue->id = l->room_start;
	queue->next = NULL;
	begin = queue;

	while (begin && begin->id != 5)
	{
		visited[begin->id] = 1;
		cut_paths(l, begin->id);
		int	j;
		t_queue	*temp;

		j = 0;
		temp = NULL;
		while (j < l->nb_rooms)
		{
			if (l->pipes[begin->id][j] == 1 && visited[j] == 0)
			{
	//			printf("begin id  = %d\n", begin->id);
				queue->next = (t_queue*)malloc(sizeof(t_queue));
				queue = queue->next;
				queue->next = NULL;
				queue->id = j;
				visited[queue->id] = 1;
			}
			j++;
		}
		temp = begin;
		if (begin->next)
		{
			begin = begin->next;
		}
		free(temp);
	}
	free(visited);
	free(begin);
}

int	main(int argc, char **argv)
{
	t_lemin	l;


	init_struct_lemin(&l);
	init_arguments(argc, argv, &l);
	get_file(&l);
	ft_putendl(l.string_file);

	//parsing
	parsing_ants_number(&l);
	if (parsing_room_and_stock(&l) == 2)
		free_check_if_room(&l,
				"\033[091mErreur : La map est mal formatee\033[0m");
	make_tab_equivalence(&l);
	parsing_pipes_and_stock(&l);
	check_end_and_start(&l);

	// resolve
	
	create_sum_tab(&l);
	update_sum_tab(&l);

	if (l.debug == 1)
	{
		print_resume(&l);
		print_equivalence_tab(&l);
		ft_print_tab_pipes(&l);
	}


	cut_paths(&l, l.room_end);
	bfs(&l);
	check_for_isolated_rooms(&l);


	count_nb_paths(&l);


	free(l.sum);
	ft_memdel((void**)&l.string_file);
	ft_free_double_tab((void**)l.file);
	ft_free_double_tab((void**)l.eq);
	ft_free_double_tab((void**)l.pipes);
	free_lst_name(&l);

	return (0);
}
