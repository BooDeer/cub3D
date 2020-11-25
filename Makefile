# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/25 09:27:51 by hboudhir          #+#    #+#              #
#    Updated: 2020/11/25 18:21:05 by hboudhir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
AR = ar
NAME = cub3d.a
LIB = cub3d.h
flags = -Wall -Wextra -Werror
FILES = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c drawing.c  \
	main.c map_tools.c map_tools2.c map_tools3.c map_tools4.c math_functs.c player.c \
	player_2.c ray_casting.c ray_casting2.c screenshot.c sprite.c walls.c map.c \
	my_lifbt/ft_atoi.c my_lifbt/ft_bzero.c my_lifbt/ft_strncmp.c \
	my_lifbt/ft_isalpha.c my_lifbt/ft_isdigit.c my_lifbt/ft_memcpy.c \
	my_lifbt/ft_split.c

OBJ = get_next_line.o get_next_line_utils.o drawing.o  \
	main.o map_tools.o map_tools2.o map_tools3.o map_tools4.o math_functs.o player.o \
	player_2.o ray_casting.o ray_casting2.o screenshot.o sprite.o walls.o map.o \
	ft_atoi.o ft_bzero.o ft_strncmp.o ft_isalpha.o ft_isdigit.o ft_memcpy.o ft_split.o

all: $(NAME)
	@echo "Creating the library."
	@$(CC) -fsanitize=address -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit $(NAME) -o cub3d
$(NAME):
	@$(CC) $(flags) -c $(FILES)
	@$(AR) rc $(NAME) $(OBJ)
	@ranlib $(NAME)
clean:
	@echo "Cleaning *.o files."
	@rm -rf $(OBJ)
fclean: clean
	@echo "Cleaning all files."
	@rm -rf $(NAME) cub3d
bonus:
	@echo "Nothing here."
re: fclean all
	@echo "Recreating the library."