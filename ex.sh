make -C libft/ re
gcc -Wall -Wextra -Werror -o test test_input_reader.c flood_fill.c init_struct.c input_reader.c libft/libft.a -I libft
make -C libft/ fclean
