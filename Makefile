# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiseo <jiseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/23 14:34:40 by jiseo             #+#    #+#              #
#    Updated: 2021/01/26 01:59:43 by kycho            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
LIBFT			=	./libft/libft.a
SRCS_PATH		=	./srcs/
INCS			=	-Iincludes
RAW_SRCS		=	main.c \
					init_signal.c \
					get_next_line.c \
					check_input_valid.c \
					\
					prompt/prompt.c \
					\
					init_free_msh/init_msh.c \
					init_free_msh/free_msh_member.c \
					\
					parsing/parsing.c \
					parsing/split_token.c \
					parsing/making_cmd.c \
					parsing/sanitize_token.c \
					parsing/sanitize_env.c \
					parsing/get_env_replaced_input.c \
					\
					executing/executing.c \
					executing/set_redirection_fd.c \
					executing/basic_executor.c \
					executing/create_process.c \
					executing/piping.c \
					\
					builtins/get_builtin_executor.c \
					builtins/run_builtin_executor.c \
					builtins/do_cd.c \
					builtins/do_echo.c \
					builtins/do_env.c \
					builtins/do_exit.c \
					builtins/do_export.c \
					builtins/do_pwd.c \
					builtins/do_unset.c \
					\
					utils/ft_double_free.c \
					utils/ft_strcmp.c \
					utils/is_in_charset.c \
					utils/get_env_dict.c \
					utils/set_env_dict.c \
					utils/unset_env_dict.c \
					utils/quick_sort_env.c \
					utils/append_char_to_str.c \
					utils/is_numeric_str.c \
					utils/is_numeric_long_str.c \
					utils/insert_char_before_set.c \
					utils/is_fine_env_key.c \
					utils/split_path.c \
					utils/get_env_array.c \
					utils/get_upper_path.c \
					\
					errors/exit_print_err.c \
					errors/print_syntax_err.c \
					errors/print_execute_err.c \
					errors/print_shlvl_err.c \
					errors/print_identifier_err.c \

SRCS			=	$(addprefix $(SRCS_PATH), $(RAW_SRCS))
OBJS			=	$(SRCS:.c=.o)
CC				= 	gcc
CFLAGS 			=	-Wall -Wextra -Werror
LIB				=	-Llibft -lft
LIBFT			=	./libft
RM				= 	rm -f

.PHONY : all clean fclean re val r

all:			$(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LIB) $(INCS) #-g -fsanitize=address


.c.o:
	$(CC) $(CFLAGS) $(INCS) -c $< -o $(<:.c=.o) #-g -fsanitize=address

clean:
	$(MAKE) -C $(LIBFT) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

val:
	valgrind --leak-check=full --show-leak-kinds=all --error-limit=no --track-origins=yes ./minishell

r: all
	./minishell
