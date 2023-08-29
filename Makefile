# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 11:29:22 by gmiyakaw          #+#    #+#              #
#    Updated: 2023/08/05 14:45:02 by kfortin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################################################
#							    PROGRAM NAMES	      					  	  #
###############################################################################

NAME		=	minishell
HEADER_F	=	minishell.h

###############################################################################
#							    SYSTEM VARIABLES       					  	  #
###############################################################################

# CFLAGS			=	-Wall -Werror -Wextra -fsanitize=address -g

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra -g
RM 				=	rm -rf

###############################################################################
#							 DIRECTORIES AND PATHS						  	  #
###############################################################################

# INCLUDES and LIBRARIES
INCLUDE_DIR		=	includes/

LIBFT_DIR		=	$(INCLUDE_DIR)libft/
LIBFT_H			=	$(LIBFT_DIR)libft.h

LIBRL_DIR		=	$(INCLUDE_DIR)readline/
LIBRL_H			=	chardefs.h history.h keymaps.h readline.h rlconf.h rlstdc.h rltypedefs.h tilde.h


SRC_DIR			=	src/
BUILTIN_DIR		=	$(SRC_DIR)builtins/

OBJ_DIR		=	obj/

###############################################################################
#							 		FILES								  	  #
###############################################################################

SRC_FILES		=	00.00-main.c 						\
					00.01-ft_split_struct_quoted.c 		\
					00.02-ft_initiate_struct.c 			\
					00.03-free_data.c					\
					00.04-lexical_utilis.c				\
					00.05-lexical_utilis_2.c			\
					00.06-ft_split_struct_utilis.c		\
					00.07-free_data_2.c 				\
					00.08-ft_split_struct_quoted_2.c	\
					00.09-ft_initiate_struct_2.c 		\
					01.01-ft_split_struct.c 			\
					01.02-parser.c 						\
					01.03-syntax_checkers.c 			\
					01.04-cmd_table.c					\
					01.05-cmd_table2.c					\
					01.06-expansions.c					\
					01.07-expansions2.c					\
					01.08-heredoc.c						\
					01.09-heredoc2.c					\
					01.10-open_functions.c				\
					01.11-open_functions2.c				\
					01.12-join_args.c					\
					01.13-ft_split_struct_utilis.c 		\
					01.14-init_cmd_table.c 				\
					02.01-execution.c					\
					02.02-execution_builtins.c 			\
					02.03-signal.c						\
					02.04-single_cmd.c					\
					02.05-execution_utilis.c			\
					02.06-execution_builtins_2.c 		\
					03.01-error_exit.c 					\
					03.02-test_print.c					\
					03.03-misc_utils.c					\
					03.04-misc_utils_2.c				\

BUILTIN_FILES		=	export.c					\
						export2.c					\
						export3.c					\
						export4.c					\
						export_no_arg.c				\
						export_no_arg_utilis.c		\
						echo.c						\
						echo_utilis.c 				\
						pwd.c						\
						exit.c						\
						exit_utilis.c				\
						exit_utilis_2.c				\
						env.c						\
						cd.c						\
						unset.c						\

OBJS			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
OBJ_FILES		=	$(BUILTIN_FILES:.c=.o) $(SRC_FILES:.c=.o)

RL_HEADER		=	$(addprefix $(LIBRL_DIR), $(LIBRL_H))
HEADER			=	$(addprefix $(INCLUDE_DIR), $(HEADER_F)) $(RL_HEADER)

VPATH			=	$(SRC_DIR) $(BUILTIN_DIR) 

$(OBJ_DIR)%.o: %.c $(SRC_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -I $(LIBRL_DIR) -I $(LIBFT_DIR) -c $< -g -o $@ -static

###############################################################################
#							 		RECIPES								  	  #
###############################################################################

all:	obj $(NAME)

$(NAME):	$(OBJ_DIR) $(OBJS)
	@make --silent -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -lcurses -lreadline $(LIBFT_DIR)libft.a $(LIBRL_DIR)libreadline.a $(LIBRL_DIR)libhistory.a -o $(NAME)

obj:
	mkdir -p $(OBJ_DIR)

leak:		obj $(NAME)
	rm -f report.txt
	@exec 3<>report.txt;valgrind --suppressions=ignore_rdl_leaks.txt --partial-loads-ok=yes --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --log-fd=3 ./minishell

fd : $(NAME)
	valgrind --track-fds=yes --trace-children=yes ./minishell

clean:
	@$(RM) $(OBJS)
	@make -C $(LIBFT_DIR) fclean

fclean:		clean
	@$(RM) $(NAME)
	@$(RM) $(NAME).dSYM*
	@$(RM) $(OBJ_DIR)
	@$(RM) $(LIBFT_DIR)libft.a
	@make -C $(LIBFT_DIR) clean

re:		fclean all

.PHONY: all clean fclean re leak
