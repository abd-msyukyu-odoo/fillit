/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 18:40:47 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/28 17:57:06 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	localize(char **tetro, TETRO *piece, int x, int y)
{
	tetro[y][x] = 'x';
	if (x > piece->footprint.x)
		piece->footprint.x = x;
	if (x < piece->origin.x)
		piece->origin.x = x;
	if (y > piece->footprint.y)
		piece->footprint.y = y;
	if (y < piece->origin.y)
		piece->origin.y = y;
}

static void	flooder(char **tetro, TETRO *piece, int x, int y)
{
	int		inc;
	int		i;

	i = -1;
	inc = 1;
	while (++i <= 1)
	{
		if ((y - inc) > -1 && (y - inc) < TETRO_SIZE &&
				tetro[y - inc][x] == '#')
		{
			localize(tetro, piece, x, y - inc);
			flooder(tetro, piece, x, y - inc);
		}
		if ((x - inc) > -1 && (x - inc) < TETRO_SIZE &&
				tetro[y][x - inc] == '#')
		{
			localize(tetro, piece, x - inc, y);
			flooder(tetro, piece, x - inc, y);
		}
		inc = -1;
	}
}

static int	check_tetro(char **tetro, TETRO *piece)
{
	CHECK index;

	init_check(&index);
	while (tetro[index.y])
	{
		while (tetro[index.y][index.x])
		{
			if (tetro[index.y][index.x] == '#')
			{
				free(piece);
				return (0);
			}
			else if (tetro[index.y][index.x] == 'x')
			{
				piece->pattern[index.index].x = index.x;
				piece->pattern[index.index].y = index.y;
				index.index += 1;
			}
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

	piece = (TETRO *)malloc(sizeof(TETRO));
	init_tetro(piece);
	init_check(&index);
	index.index = -1;
	if (!tetro_in)
		return (NULL);
	while (index.y < TETRO_SIZE)
	{
		while (tetro_in[index.y][index.x] && tetro_in[index.y][index.x] != '#')
			index.x += 1;
		if (tetro_in[index.y][index.x] == '#')
		{
			piece->origin.x = TETRO_SIZE - 1;
			piece->origin.y = TETRO_SIZE - 1;
			flooder(tetro_in, piece, index.x, index.y);
			return ((check_tetro(tetro_in, piece)) ? piece : NULL);
		}
		index.x = 0;
		index.y += 1;
	}
	return (NULL);
}
