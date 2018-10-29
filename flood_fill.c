/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 18:40:47 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/29 13:41:05 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	localize(char **tetro, TETRO *piece, int x, int y)
{
	tetro[y][x] = 'x';
	if (x > piece->footprint.x)
		piece->footprint.x = x;
	else if (x < piece->origin.x)
		piece->origin.x = x;
	if (y > piece->footprint.y)
		piece->footprint.y = y;
	else if (y < piece->origin.y)
		piece->origin.y = y;
}

static void	flooder(char **tetro, TETRO *piece, int x, int y)
{
	int		inc;
	int		i;
	COORD	pos;

	i = -1;
	inc = 1;
	while (++i <= 1)
	{
		pos.y = y - inc;
		if (pos.y > -1 && pos.y < TETRO_SIZE && tetro[pos.y][x] == '#')
		{
			localize(tetro, piece, x, pos.y);
			flooder(tetro, piece, x, pos.y);
		}
		pos.x = x - inc;
		if (pos.x > -1 && pos.x < TETRO_SIZE && tetro[y][pos.x] == '#')
		{
			localize(tetro, piece, pos.x, y);
			flooder(tetro, piece, pos.x, y);
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
	if (!tetro_in || !piece)
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
