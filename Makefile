# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mochaoui <mochaoui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 15:33:15 by mochaoui          #+#    #+#              #
#    Updated: 2023/10/02 23:18:48 by mochaoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang -g3 -Wall -Werror -Wextra

C_FLAGS =  -lreadline  -fsanitize=address -g3

C_FILES = 	main.c just_split.c tools.c lsts.c pipe_exec.c get_next_line.c \
		get_next_line_utls.c exec_utls.c expanding.c here_doc.c \
		builtins.c cd.c export.c export2.c signals.c unset.c listt.c \
		checking_errors.c utls_exe.c just_itoa.c execution_pipes.c execution_single.c \
		execution_pipes1.c execution_single1.c parce1.c parce2.c env_tools.c free_tree.c \
		exec_utls1.c expanding_tools.c ft_echo.c tools_1.c here_doc_tools.c main_finish.c \
	


OBJ=$(C_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(C_FLAGS) $(OBJ) -o $(NAME)

clean:
	rm  -f $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
