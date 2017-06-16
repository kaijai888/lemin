# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kzeng <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/23 17:30:45 by kzeng             #+#    #+#              #
#    Updated: 2017/03/23 17:30:46 by kzeng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CC = gcc
FLAG = -Wall -Wextra -Werror

SRC = ./src/lemin_main.c

LINK = -L ./src/ -llemin

RM = rm -rf

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	make -C src/
	$(CC) $(FLAG) $(SRC) -o $(NAME) $(LINK)

clean:
	make -C src/ clean
	make -C src/ clean

fclean: clean
	$(RM) $(NAME)
	make -C src/ fclean
	make -C src/ fclean

re: fclean all
