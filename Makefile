# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/04 12:40:14 by dabeloos          #+#    #+#              #
#    Updated: 2018/12/07 17:29:50 by dabeloos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fillit

C_FILES		= flood_fill.c \
			  init_struct.c \
			  input_reader.c \
			  solver.c \
			  closed_gap.c \
			  main.c \
			  same_pattern.c

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
