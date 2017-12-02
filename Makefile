# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdubus <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/05 19:12:36 by mdubus            #+#    #+#              #
#    Updated: 2017/11/29 18:23:22 by mdubus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	clang
NAME		=	lem-in
FLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address
#FLAGS		=	-Wall -Wextra -Werror -g
VISU		=	visu
LIBDIR		=	libft
LIBLINK		=	-L $(LIBDIR) -lft
LIB 		=	$(LIBDIR)/libft.a
LIB_VISU	=	-L ~/.brew/lib -lSDL2 -lSDL2_ttf -lSDL2_image

INCLUDES	= 	-I ./includes
INCLUDE		=	./includes
INCLUDES_VISU	=	-I ~/.brew/include/SDL2/ -D_THREAD_SAFE

OBJDIR		= 	objs

OBJDIR_ALGO	=	objs/algorithm
OBJDIR_PARSING	=	objs/parsing
OBJDIR_VISU	=	objs/visualizer

SRCDIR_ALGO	=	srcs/algorithm
SRCDIR_PARSING	=	srcs/parsing
SRCDIR_VISU	=	srcs/visualizer

SRC_ALGO	=	main.c debug_mode.c\
				resolve_isolated_roms.c resolve_count_nb_paths.c graph.c\
				print.c resolve_remove_useless_paths.c free2.c\
				resolve_check_if_solution_exists.c resolve_bfs.c resolve.c\
				resolve_delete_other_paths.c resolve_nb_paths.c\
				resolve_calculate_different_paths.c print_tab_pipes.c\
				resolve_get_ants.c resolve_create_ant_result.c

SRC_PARSING	=	parsing.c parsing_ants_number.c parsing_start_end_exists.c\
				parsing_check_if_room.c parsing_room_and_stock.c\
				parsing_pipes_and_stock.c parsing_check_room_name.c\
				parsing_check_end_and_start.c get_file.c free.c useful.c\
				init.c

SRC_VISU	=	main.c useful.c init.c loop.c stock_rooms.c free.c\
				visu_parsing_pipes.c stock_turns.c print.c draw_rooms.c

OBJS_ALGO	=	$(addprefix $(OBJDIR_ALGO)/, $(SRC_ALGO:.c=.o))\
				$(addprefix $(OBJDIR_PARSING)/, $(SRC_PARSING:.c=.o))

OBJS_VISU	=	$(addprefix $(OBJDIR_VISU)/, $(SRC_VISU:.c=.o))\
				$(addprefix $(OBJDIR_PARSING)/, $(SRC_PARSING:.c=.o))

all: directory $(NAME) $(VISU) Makefile

$(NAME): $(OBJDIR_ALGO) $(LIB) $(OBJS_ALGO) $(INCLUDE)
	@$(CC) $(FLAGS) -o $@ $(OBJS_ALGO) $(LIBLINK)

$(VISU): $(OBJDIR_VISU) $(LIB) $(OBJS_VISU) $(INCLUDE)
	@$(CC) $(FLAGS) -o $@ $(OBJS_VISU) $(LIBLINK) $(LIB_VISU)

$(LIB):
	@make -C $(LIBDIR)

$(OBJDIR_ALGO)/%.o: $(SRCDIR_ALGO)/%.c
	@$(CC) $(FLAGS) -c $^ -o $@ $(INCLUDES)

$(OBJDIR_PARSING)/%.o: $(SRCDIR_PARSING)/%.c
	@$(CC) $(FLAGS) -c $^ -o $@ $(INCLUDES)

$(OBJDIR_VISU)/%.o: $(SRCDIR_VISU)/%.c
	@$(CC) $(FLAGS) -c $^ -o $@ $(INCLUDES) $(INCLUDES_VISU)

directory: $(OBJDIR) $(OBJDIR_ALGO) $(OBJDIR_VISU) $(OBJDIR_PARSING)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR_ALGO):
	@mkdir -p $(OBJDIR_ALGO)

$(OBJDIR_PARSING):
	@mkdir -p $(OBJDIR_PARSING)

$(OBJDIR_VISU):
	@mkdir -p $(OBJDIR_VISU)

clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBDIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(VISU)
	@make -C $(LIBDIR) fclean

re: fclean all

.PHONY: clean all re fclean directory
