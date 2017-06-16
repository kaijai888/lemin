# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kzeng <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/23 17:40:02 by kzeng             #+#    #+#              #
#    Updated: 2017/03/23 17:40:03 by kzeng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = liblemin.a
CC = gcc
FLAG = -c -Wall -Wextra -Werror
SRC = ft_add_link.c \
		ft_cost.c \
		ft_lemin_helper.c \
		ft_lemin_helper2.c \
		ft_lemin_helper3.c \
		ft_parse_input.c \
		ft_printf.c \
		ft_solve.c \
		get_next_line.c \

OBJ = $(SRC:.c=.o)

INC = -I lemin.h
AR = ar rc
RM = rm -rf

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(FLAG) $(INC) -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
