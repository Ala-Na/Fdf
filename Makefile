# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anadege <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/22 15:37:49 by anadege           #+#    #+#              #
#    Updated: 2021/07/10 16:19:50 by anadege          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ./srcs/adjustments.c \
		  ./srcs/errors.c \
		  ./srcs/exit.c \
		  ./srcs/hooks.c \
		  ./srcs/image.c \
		  ./srcs/main.c \
		  ./srcs/modifications.c \
		  ./srcs/parsing.c \
		  ./srcs/read_map.c \
		  ./srcs/representation.c \
		  ./srcs/transformation.c \
		  ./srcs/utils_1.c \
		  ./srcs/utils_2.c

HEADERS_FILE = includes

NAME = fdf

CC	= cc

CFLAGS	= -Wall -Wextra -Werror

OBJS	= ${SRCS:.c=.o}

LIBS	= ./minilibx-linux/libmlx.a ./minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm

%.o: %.c
		${CC} -g ${CFLAGS} -I ${HEADERS_FILE} -o $@ -c $<


all:		mlx ${NAME}
	@echo "\n\nWelcome to fdf project.\n./fdf must receive a compatible map as argument (only digits and constant number of elements per line).\nA window with the 2D representation of 3D coordinates will be displayed.\n\nYou can use keyboards for more fun !\n\n\tUP - DOWN - RIGHT - LEFT : deplace the object inside the window.\n\tSPACE : Return display to original state.\n\tC : Change vue from isometric to plane.\n\tESC : Close the window and exit the program.\n\nEnjoy !\n"


${NAME}:	${OBJS}
		${CC} -o ${NAME} ${OBJS} ${LIBS}

mlx:
		@make -C ./minilibx-linux

clean:
		@rm -f ${OBJS}

fclean: 	clean
		@rm -f ${NAME}

re:		fclean all

.PHONY: all clean re
