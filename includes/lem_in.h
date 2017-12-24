/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:34:14 by mdubus            #+#    #+#             */
/*   Updated: 2017/12/13 18:01:21 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <stdbool.h>
#pragma GCC diagnostic error "-Weverything"

# define SNORLAX 3
# define LAVA 4

typedef struct		s_room
{
	struct s_room	*next;
	int				id;
	int				ant;
	int				special;
	int				length;
	char			*name;
}					t_room;

typedef struct		s_path
{
	struct s_path	*next;
	int				*path;
	int				nbr_coups;
	int				different_path;
	int				nbr_coups_min;
	int				nbr;
	int				padding[2];
}					t_path;

typedef struct		s_queue
{
	int				id;
	int				padding[3];
	struct s_queue	*next;
}					t_queue;

typedef struct		s_lemin
{
	struct s_path	*path;
	struct s_path	*path_begin;
	struct s_path	*best_path;
	struct s_path	*solution;
	struct s_path	*solution_begin;
	struct s_room	*room;
	struct s_room	*begin;
	struct s_room	**result;
	int				*sum;
	int				*lookup;
	int				*level;
	int				*sorted;
	char			**eq;
	char			**f;
	char			*string_file;
	bool			**pipes;
	bool			*visited;
	int				nb_ants;
	int				nb_pipes;
	int				nb_rooms;
	int				flag_start;
	int				flag_end;
	int				id;
	int				comments;
	int				commands;
	int				start;
	int				nb_path;
	int				nb_path_final;
	int				ant_finish;
	int				room_start;
	int				room_end;
	int				padding;
	int				froom1;
	int				froom2;
	char			debug;
	char			graph;
	char			padding1[6];
	bool			flag_start_to_end;
	bool			flag_lava;
	bool			flag_snorlax;
	bool			padding2[1];
}					t_lemin;

void				export_graph(bool **pipes, t_lemin *l);
void				init_struct_lemin(t_lemin *l);
void				init_arguments(int argc, char **argv, t_lemin *l);
void				get_file(t_lemin *l);
void				error_lem_in(void (*function)(const char *, int fd),
					const char *str, int fd, t_lemin *l);

/*
****************************** Free ******************************************
*/

void				free_l_file(char **str);
void				free_parsing_start(t_lemin *l, char *str);
void				free_parsing_end(t_lemin *l, char *str);
void				free_check_if_room(t_lemin *l, char *str);
void				free_lst_name(t_lemin *l);
void				ft_free_tab_bool(bool **tab);
void				free_queue(t_queue *lst);
void				free_pipes(t_lemin *l, char *str);
void				free_pipes_and_sum(t_lemin *l, char *str);
void				free_at_end(t_lemin *l);
void				free_result(t_lemin *l);

/*
***************************** Parsing *****************************************
*/

void				parsing(t_lemin *l);
void				parsing_ants_number(t_lemin *l);
void				parsing_start_end_exists(t_lemin *l);
void				parsing_rooms_error_cases(t_lemin *l);
void				parsing_room_name(t_lemin *l);
int					check_if_room(char *str, t_lemin *l);
int					parsing_room_and_stock(t_lemin *l);
void				check_end_and_start(t_lemin *l);
int					parsing_pipes_and_stock(t_lemin *l);
void				check_is_print(char *str, t_lemin *l);
void				check_begin_with_l(char *str, t_lemin *l);
void				check_for_hyphen(char **tab, t_lemin *l);
void				check_if_name_already_exists(char **tab, t_lemin *l);
void				which_command(t_lemin *l, int i);
void				check_coordonates(char **tab, t_lemin *l);
void				parsing_init_tab_pipes(t_lemin *l);
void				stock_pipes(char *str, t_lemin *l);

/*
***************************** Resolve *****************************************
*/

void				check_for_isolated_rooms(t_lemin *l);
void				update_sum_tab(t_lemin *l);
void				create_sum_tab(t_lemin *l);
void				count_nb_paths(t_lemin *l);
void				bfs(t_lemin *l, int room_start);
void				check_if_solution_exists(t_lemin *l);
void				resolve(t_lemin *l);
void				remove_useless_paths(t_lemin *l);
void				delete_other_paths(t_lemin *l);
void				calculate_different_paths(t_lemin *l);
void				already_explored(t_lemin *l, int *j, int room, int i);
void				back_in_stack(t_lemin *l, int *j, int room, int i);
int					resolve_nb_paths(t_lemin *l, int room, int *j);
void				get_ants(t_lemin *l);
void				create_ant_result(t_lemin *l);

/*
***************************** Print *****************************************
*/

void				print_equivalence_tab(t_lemin *l);
void				ft_print_tab_pipes(t_lemin *l);
void				print_resume(t_lemin *l);
void				print_possible_paths(t_lemin *l);
void				print_result(t_lemin *l);
void				print_debug(t_lemin *l);

#endif
