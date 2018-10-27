/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:17:00 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/27 14:43:53 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"


static void	localize(char **tetro, CHECK *index, TETRO *piece)
{

	tetro[index->y][index->x] = '.';
	if (index->x > piece->footprint.x)
		piece->footprint.x = index->x;
	if (index->x < piece->origin.x)
		piece->origin.x = index->x;
	if (index->y > piece->footprint.y)
		piece->footprint.y = index->y;
	if (index->y < piece->origin.y)
		piece->origin.y = index->y;
	piece->pattern[index->index].x = index->x;
	piece->pattern[index->index].y = index->y;
}

CHECK *ft_check_of(int x, int y, int index)
{
	CHECK *ret;

	ret = (CHECK*)malloc(sizeof(CHECK));
	ret->x = x;
	ret->y = y;
	ret->index = index;
	return (ret);
}

static void	flooder(char **tetro, CHECK index, TETRO *piece)
{
	int		inc;
	int		i;
	CHECK	*tmp;

	i = -1;
	inc = 1;
	while (++i <= 1)
	{
		if (index.y < 4 && index.x < 4 && index.x > -1 && index.y > -1)
		{
			if ((index.y - inc) > -1 && (index.y - inc) < 4 &&
				   	tetro[index.y - inc][index.x] == '#')
			{
				localize(tetro, (tmp = ft_check_of(index.x,
					index.y - inc, (index.index += 1))),piece);
				flooder(tetro, *tmp, piece);
			}
			if ((index.x - inc) > -1 && (index.x - inc) < 4 &&
				   	tetro[index.y][index.x - inc] == '#')
			{
				localize(tetro, (tmp = ft_check_of(index.x - inc,
						index.y, (index.index += 1))),piece);
				flooder(tetro, *tmp, piece);
			}
		}
		inc = -1;
	}
}

static int	check_tetro(char **tetro)
{
	CHECK index;

	index.y = 0;
	index.x = 0;
	while (tetro[index.y])
	{
		while (tetro[index.y][index.x])
		{
			if (tetro[index.y][index.x] == '#')
				return (0);
			index.x += 1;
		}
		index.x = 0;
		index.y += 1;
	}
	return (1);
}



TETRO		*flood_fill(char **tetro_in)
{
	CHECK	index;
	TETRO	*piece;
	
	piece = (TETRO*)malloc(sizeof(TETRO));
	init_tetro(piece);
	index.index = -1;
	if (!tetro_in)
		return (NULL);
	while (index.y < 4)
	{
		while(tetro_in[index.y][index.x] && tetro_in[index.y][index.x] != '#')
			index.x += 1;
		if (tetro_in[index.y][index.x] == '#')
		{
			piece->origin.x = 3;
			piece->origin.y = 3;
			flooder(tetro_in, index, piece);
			return ((check_tetro(tetro_in)) ? piece : NULL);
		}
		index.x = 0;
		index.y += 1;
	}
	return (NULL);
}
