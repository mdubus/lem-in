/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:34:14 by mdubus            #+#    #+#             */
/*   Updated: 2017/11/11 16:50:16 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct		s_room
{
	int				id;
	int				padding2;
	char			*name;
	struct s_room	*next;
}					t_room;

typedef struct		s_path
{
	struct s_path	*next;
	int				*path;
	int				nbr_coups;
	char		padding2[4];
}					t_path;


typedef struct	s_lemin
{
	int			nb_ants;
	int			nb_pipes;
	int			nb_rooms;
	int			flag_start;
	int			flag_end;
	int			id;
	int			comments;
	int			commands;
	int			start;
	int			nb_path;
	int			room_start;
	int			room_end;
	int			*sum;
	bool		**pipes; //stock les relations entre les pipes
	int			*lookup; // permet de savoir si on est deja passe par ce chemin
	int			*sorted;
	char		*string_file; // contient tout le fichier dans une string
	char		**eq; // equivalence nom / id
	char		**file; // contient tout le fichier dans un tableau
	char		debug;
	char		graph;
	char		padding1[6];
	struct s_room	*room;
	struct s_room	*begin;
	struct s_path	*path;
	struct s_path	*path_begin;
}				t_lemin;



void	export_graph(bool **pipes, t_lemin *l);


void	init_struct_lemin(t_lemin *l);
void	init_arguments(int argc, char **argv, t_lemin *l);
void	get_file(t_lemin *l);
void	error_lem_in(void (*function)(const char *, int fd),
		const char *str, int fd, t_lemin *l)__attribute__ ((noreturn));








/*
****************************** Free ******************************************
*/

void	free_l_file(char **str);
void	free_parsing_start(t_lemin *l, char *str)__attribute__ ((noreturn));
void	free_parsing_end(t_lemin *l, char *str)__attribute__ ((noreturn));
void	free_check_if_room(t_lemin *l, char *str)__attribute__((noreturn));
void	free_lst_name(t_lemin *l);






/*
***************************** Parsing *****************************************
*/

void	parsing_ants_number(t_lemin *l);
void	parsing_start_end_exists(t_lemin *l);
void	parsing_rooms_error_cases(t_lemin *l);
void	parsing_room_name(t_lemin *l);
int		check_if_room(char *str, t_lemin *l);
int		parsing_room_and_stock(t_lemin *l);
void	check_end_and_start(t_lemin *l);
int			parsing_pipes_and_stock(t_lemin *l);

/*
***************************** Resolve *****************************************
*/

void	check_for_isolated_rooms(t_lemin *l);
void		update_sum_tab(t_lemin *l);
void	create_sum_tab(t_lemin *l);
void	count_nb_paths(t_lemin *l);




/*
***************************** Print *****************************************
*/

void	print_equivalence_tab(t_lemin *l);
void	ft_print_tab_pipes(t_lemin *l);
void	print_resume(t_lemin *l);

#endif
