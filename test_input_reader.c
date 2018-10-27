/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_input_reader.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 13:52:02 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/27 15:06:07 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

void	display_tetro(TETRO *tetro)
{
	char	**tetro_array;
	int		i;

	tetro_array = (char **)malloc(sizeof(char *) * (TETRO_SIZE + 1));
	tetro_array[TETRO_SIZE] = NULL;
	i = -1;
	while (++i < TETRO_SIZE)
	{
		tetro_array[i] = ft_strnew(TETRO_SIZE);
		tetro_array[i] = ft_memset(tetro_array[i], ' ', TETRO_SIZE);
	}
	i = -1;
	while (++i < TETRO_SIZE)
		tetro_array[tetro->pattern[i].x][tetro->pattern[i].y] = '%';
	i = -1;
	while (++i < TETRO_SIZE)
		printf("%s\n", tetro_array[i]);
	printf("\n");
	ft_array_strdel(&tetro_array);
}

int		main(int argc, char **argv)
{
	TETRO	**list_tetro;

	if (argc == 2)
	{
		list_tetro = read_file(argv[1]);
		while (list_tetro)
		{
			display_tetro(*list_tetro);
			++list_tetro;
		}
	}
	return (0);
}
