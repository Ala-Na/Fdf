# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anadege <anadege@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/28 15:16:48 by anadege           #+#    #+#              #
#    Updated: 2021/06/28 15:19:30 by anadege          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= Fdf

INC		=

SRCS	= ./main.c ./brasenham.c

OBJS	= $(subst .c,.o,$(SRCS)))

FLAGS	= -Wall -Wextra -Werror

LIBX	= ./minilibx-linux/libmlx.a ./minilibx-linux/libmlx_Linux.a -I ./minilibx-linux/ -lXext -lX11 -lm -lz

