# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdubus <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/05 19:12:36 by mdubus            #+#    #+#              #
#    Updated: 2017/11/18 16:56:00 by mdubus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	clang
NAME		=	lem-in
#FLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address
FLAGS		=	-Wall -Wextra -Werror -g
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
OBJDIR_VISU	=	objs/visualizer

SRCDIR_ALGO	=	srcs/algorithm
SRCDIR_VISU	=	srcs/visualizer

SRC_ALGO	=	main.c  get_file.c parsing_ants_number.c useful.c\
				parsing_start_end_exists.c parsing_check_if_room.c free.c\
				parsing_room_and_stock.c parsing_pipes_and_stock.c init.c\
				resolve_isolated_roms.c resolve_count_nb_paths.c graph.c\
				print.c resolve_remove_useless_paths.c parsing.c\
				resolve_check_if_solution_exists.c resolve_bfs.c resolve.c\
				parsing_check_room_name.c parsing_check_end_and_start.c\
				resolve_delete_other_paths.c resolve_nb_paths.c\
				resolve_calculate_different_paths.c

SRC_VISU	=	main.c

OBJ_ALGO	=	$(SRC_ALGO:.c=.o)
OBJ_VISU	=	$(SRC_VISU:.c=.o)

SRCS_ALGO	=	$(addprefix $(SRCDIR_ALGO)/, $(SRC_ALGO))
OBJS_ALGO	=	$(addprefix $(OBJDIR_ALGO)/, $(SRC_ALGO:.c=.o))

SRCS_VISU	=	$(addprefix $(SRCDIR_VISU)/, $(SRC_VISU))
OBJS_VISU	=	$(addprefix $(OBJDIR_VISU)/, $(SRC_VISU:.c=.o))

all: directory $(NAME) $(VISU) Makefile

$(NAME): $(OBJDIR_ALGO) $(LIB) $(OBJS_ALGO) $(INCLUDE)
	@$(CC) $(FLAGS) -o $@ $(OBJS_ALGO) $(LIBLINK)

$(VISU): $(OBJDIR_VISU) $(LIB) $(OBJS_VISU) $(INCLUDE)
	@$(CC) $(FLAGS) -o $@ $(OBJS_VISU) $(LIBLINK) $(LIB_VISU)

$(LIB):
	@make -C $(LIBDIR)

$(OBJDIR_ALGO)/%.o: $(SRCDIR_ALGO)/%.c
	@$(CC) $(FLAGS) -c $^ -o $@ $(INCLUDES)

$(OBJDIR_VISU)/%.o: $(SRCDIR_VISU)/%.c
	@$(CC) $(FLAGS) -c $^ -o $@ $(INCLUDES) $(INCLUDES_VISU)

directory: $(OBJDIR) $(OBJDIR_ALGO) $(OBJDIR_VISU)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR_ALGO):
	@mkdir -p $(OBJDIR_ALGO)

$(OBJDIR_VISU):
	@mkdir -p $(OBJDIR_VISU)

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(OBJS_ALGO)
	@make -C $(LIBDIR) clean
	@rm -rf $(OBJDIR_ALGO)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(VISU)
	@make -C $(LIBDIR) fclean

re: fclean all

.PHONY: clean all re fclean directory
