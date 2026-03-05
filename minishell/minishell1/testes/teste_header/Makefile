# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/27 07:18:00 by olacerda          #+#    #+#              #
#    Updated: 2026/02/27 07:36:53 by olacerda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = teste_makefile

CC = cc
CFLAGS = 
RM = rm -rf
OBJ_DIR = build
INCLUDES = -I. -I./includes

all: $(NAME)

SRCS =	soma.c \
		main.c \

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))	

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
