# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdubus <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/05 19:12:36 by mdubus            #+#    #+#              #
#    Updated: 2017/11/14 11:35:42 by mdubus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	clang
NAME		=	lem-in
FLAGS		=	-Wall -Wextra -Werror -Weverything -g -fsanitize=address
#FLAGS		=	-Wall -Wextra -Werror -Weverything -g
LIBDIR		=	libft
LIBLINK		=	-L $(LIBDIR) -lft
LIB 		=	$(LIBDIR)/libft.a

INCLUDES	= 	-I ./includes
INCLUDE		=	./includes

OBJDIR		= 	objs

OBJDIR_ALGO	=	objs/algorithm

SRCDIR_ALGO	=	srcs/algorithm

SRC_ALGO	=	main.c  get_file.c parsing_ants_number.c useful.c\
				parsing_start_end_exists.c parsing_check_if_room.c free.c\
				parsing_room_and_stock.c parsing_pipes_and_stock.c init.c\
				resolve_isolated_roms.c resolve_count_nb_paths.c graph.c\
				print.c resolve_remove_useless_paths.c\
				resolve_check_if_solution_exists.c

OBJ_ALGO	=	$(SRC_ALGO:.c=.o)

SRCS_ALGO	=	$(addprefix $(SRCDIR_ALGO)/, $(SRC_ALGO))
OBJS_ALGO	=	$(addprefix $(OBJDIR_ALGO)/, $(SRC_ALGO:.c=.o))


all: directory $(NAME) Makefile

$(NAME): $(OBJDIR_ALGO) $(LIB) $(OBJS_ALGO) $(INCLUDE)
	@$(CC) $(FLAGS) -o $@ $(OBJS_ALGO) $(LIBLINK)

$(LIB):
	@make -C $(LIBDIR)

$(OBJDIR_ALGO)/%.o: $(SRCDIR_ALGO)/%.c
	@$(CC) $(FLAGS) -c $^ -o $@ $(INCLUDES)

directory: $(OBJDIR) $(OBJDIR_ALGO)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR_ALGO):
	@mkdir -p $(OBJDIR_ALGO)

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(OBJS_ALGO)
	@make -C $(LIBDIR) clean
	@rm -rf $(OBJDIR_ALGO)

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all

.PHONY: clean all re fclean directory
