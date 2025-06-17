# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: salah <salah@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 17:02:36 by salhali           #+#    #+#              #
#    Updated: 2025/06/05 18:49:19 by salah            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

LIBS = -lreadline

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

SRC = builtins/builtin_echo.c \
      builtins/builtins.c \
			builtins/builtin_cd.c \
			builtins/builtin_env.c \
			builtins/builtin_unset.c \
			builtins/builtin_pwd.c \
			builtins/builtin_export.c \
			builtins/builtin_exit.c \
			tester_parsing.c \
			utils.c \
			helper.c \
			helper1.c \
			main.c \

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME) : $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY: all clean fclean re

