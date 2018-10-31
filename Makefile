# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhunders <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/31 12:29:48 by rhunders          #+#    #+#              #
#    Updated: 2018/10/31 12:29:55 by rhunders         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fillit

C_FILES		= flood_fill.c \
			  init_struct.c \
			  input_reader.c \
			  solver.c

O_FILES		= $(C_FILES:.c=.o)

FLAGS		= -c -Wall -Wextra -Werror

$(NAME):
	make -C libft/
	gcc $(FLAGS) $(C_FILES) -I./libft/
	gcc -o $(NAME) $(O_FILES) -L./libft/ -lft

all:		$(NAME)

clean:
	make -C libft/ clean
	rm -f $(O_FILES)

fclean:		clean
	rm -f $(NAME)
	make -C libft/ fclean

re:			fclean all

.PHONY: clean fclean all re
