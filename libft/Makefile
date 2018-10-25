# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/04 12:40:14 by dabeloos          #+#    #+#              #
#    Updated: 2018/10/25 15:51:42 by dabeloos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

C_FILES		= ft_memset.c \
			  ft_bzero.c \
			  ft_memcpy.c \
			  ft_memccpy.c \
			  ft_memmove.c \
			  ft_memchr.c \
			  ft_memcmp.c \
			  ft_strlen.c \
			  ft_strdup.c \
			  ft_strcpy.c \
			  ft_strncpy.c \
			  ft_strcat.c \
			  ft_strncat.c \
			  ft_strlcat.c \
			  ft_strchr.c \
			  ft_strrchr.c \
			  ft_strstr.c \
			  ft_strnstr.c \
			  ft_strcmp.c \
			  ft_strncmp.c \
			  ft_atoi.c \
			  ft_atoi2.c \
			  ft_isalpha.c \
			  ft_isdigit.c \
			  ft_isalnum.c \
			  ft_isascii.c \
			  ft_isprint.c \
			  ft_toupper.c \
			  ft_tolower.c \
			  ft_memalloc.c \
			  ft_memdel.c \
			  ft_strnew.c \
			  ft_strdel.c \
			  ft_strclr.c \
			  ft_striter.c \
			  ft_striteri.c \
			  ft_strmap.c \
			  ft_strmapi.c \
			  ft_strequ.c \
			  ft_strnequ.c \
			  ft_strsub.c \
			  ft_strsub2.c \
			  ft_strjoin.c \
			  ft_strtrim.c \
			  ft_strsplit.c \
			  ft_itoa.c \
			  ft_itoa2.c \
			  ft_strrev.c \
			  ft_putchar.c \
			  ft_putstr.c \
			  ft_putendl.c \
			  ft_putnbr.c \
			  ft_putnbr2.c \
			  ft_putchar_fd.c \
			  ft_putstr_fd.c \
			  ft_putendl_fd.c \
			  ft_putnbr_fd.c \
			  ft_putnbr2_fd.c \
			  ft_lstnew.c \
			  ft_lstdelone.c \
			  ft_lstdel.c \
			  ft_lstdel_content.c \
			  ft_lstadd.c \
			  ft_lstiter.c \
			  ft_lstmap.c \
			  ft_swap_int.c \
			  ft_sort_int.c \
			  ft_array_strdel.c \
			  ft_index_of.c \
			  get_next_line.c

O_FILES		= $(C_FILES:.c=.o)

FLAGS		= -c -Wall -Wextra -Werror

$(NAME):
			gcc $(FLAGS) $(C_FILES) -I includes
			ar -rcs $(NAME) $(O_FILES)

all:		$(NAME)

clean:
			rm -f $(O_FILES)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY: clean fclean all re
