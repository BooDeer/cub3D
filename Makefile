# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/25 09:27:51 by hboudhir          #+#    #+#              #
#    Updated: 2020/11/25 13:18:35 by hboudhir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
AR = ar
NAME = cub3d.a
LIB = cub3d.h
flags = -Wall -Wextra -Werror
FILES = 
OBJ =

all: $(NAME)
	@echo "Creating the library . . . . ."
$(NAME):
	@$(CC) $(flags) -c $(FILES) -I $(LIB)
	@$(AR) rc $(NAME) $(OBJ)
	@ranlib $(NAME)
clean:
	@echo "Cleaning *.o files . . . . ."
	@rm -rf $(OBJ)
fclean: clean
	@echo "Cleaning all files . . . . ."
	@rm -rf $(NAME)
bonus:
	@echo "Nothing here . . . . ."
re: fclean all
	@echo "Recreating the library . . . . ."