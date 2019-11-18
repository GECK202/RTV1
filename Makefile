# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vabraham <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 14:23:53 by vabraham          #+#    #+#              #
#    Updated: 2019/11/15 14:23:54 by vabraham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = main.c light.c
LIB = includes/libft/libft.a
NAME = rtv1

all:
	@gcc -L includes/libft -lft $(FILES) -I includes/libft -o $(NAME) -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
