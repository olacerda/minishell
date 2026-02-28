# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/22 23:11:08 by otlacerd          #+#    #+#              #
#    Updated: 2026/02/28 06:05:35 by olacerda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
OBJ_DIR = build
INCLUDES = -I. -I./includes
LDFLAGS = -lreadline

all: $(NAME)

SRCS =	minishell.c \
		src/execution/core_execution/core_execution.c \
		src/execution/core_execution/absolute_path.c \
		src/execution/core_execution/prefix.c \
		src/execution/core_execution/pipes.c \
		src/execution/core_execution/pid_manegement.c \
		src/execution/core_execution/redirections.c \
		src/execution/data/data.c \
		src/execution/data/list_comand.c \
		src/execution/data/list_redirections.c \
		src/execution/data/project_structure.c \
		src/general_utils/utils.c \
		src/execution/built-ins/env.c \
		src/execution/built-ins/exit.c \
		src/execution/built-ins/export.c \
		src/execution/built-ins/unset.c \
		src/execution/built-ins/echo.c \
 		src/execution/built-ins/cd.c \

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
