/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 17:57:12 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/29 01:24:06 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			init_map(MAP *map, int *try, BOX *box)
{
	int i;
	static int		result = 0;

	i = 0;
	if (!map->size)
		map->size = box->nb_tetro * TETRO_SIZE;
	while (*try || (result = map->l_map * map->l_map) < map->size)
	{
		map->l_map += 1;
		*try = 0;
	}
	if (result > map->size)
		map->size = result;
	if (!(map->board = (char**)malloc(sizeof(char*) * map->l_map)))
		return (-1);
	while (i < map->l_map)
	{
		map->board[i] = (char*)malloc(sizeof(char) * map->l_map + 1);
		ft_memset((void*)map->board[i], '.', map->l_map + 1);
		map->board[i++][map->l_map] = 0;
	}
	return(1);
}

int			fill_pattern(MAP *map, TETRO *piece, int index, COORD point)
{
	int i;

	i = 0;
	point.x -= piece->footprint.x;
	point.y -= piece->footprint.y;
	while (i < TETRO_SIZE)
	{
		if (/*(piece->pattern[i].y + point.y) < map->l_map && (piece->pattern[i].x + point.x) < map->l_map && 
		*/map->board[piece->pattern[i].y + point.y][piece->pattern[i].x + point.x] == '.')
		{
			map->board[piece->pattern[i].y + point.y][piece->pattern[i].x + point.x] = 'A' + index;
			i++;
		}
		else
		{
			i = 0;
			while (i < TETRO_SIZE)
			{
				if (/*(piece->pattern[i].y + point.y) < map->l_map && (piece->pattern[i].x + point.x) < map->l_map && 
				*/map->board[piece->pattern[i].y + point.y][piece->pattern[i].x + point.x] == 'A' + index)
				{
					map->board[piece->pattern[i].y + point.y][piece->pattern[i].x + point.x] = '.';
				}
				i++;
			}
			return (0);
		}
	}
	return (1);
}

int			erase_pattern(char **board, TETRO piece, int index, COORD point)
{
	int i;

	i = 0;
	point.x -= piece.footprint.x;
	point.y -= piece.footprint.y;
	while (i < TETRO_SIZE)
	{
		board[piece.pattern[i].y + point.y][piece.pattern[i].x + point.x] = '.';
		i++;
	}
	return (i);
}

static int	fillit(BOX *box, MAP *map, int index, int try)
{
	COORD			point;

	if (index == box->nb_tetro)
		return (1);
	if (try)
		if (init_map(map, &try, box) == -1)
			return (0);
	point.x = box->tetro_box[index]->footprint.x;
	point.y = box->tetro_box[index]->footprint.y;
	while (point.y < map->l_map)
	{
		while (point.x < map->l_map)
		{
			if (fill_pattern(map, box->tetro_box[index], index, point))
			{
				if (fillit(box, map, index + 1, 0))
				{
					return (1);
				}
				erase_pattern(map->board, *box->tetro_box[index], index, point);
			}
			point.x += 1;
		}
		point.x = box->tetro_box[index]->footprint.x;
		point.y += 1;
	}
	if (!index)
		return (fillit(box, map, 0, 1));
	return (0);
}

int			main(int arc, char **argv)
{
	BOX		*box;
	MAP		map;
	int		i;

	i = 0;
	map.size = 0;
	map.l_map = 0;
	if (arc != 2)
		return (0);
	if (!(box = read_file(argv[1])))
	{
		ft_putendl("invalid tetrominos");
		return (0);
	}
	if (!(fillit(box, &map, 0, 1)))
	{
		ft_putendl("backtrack error");
		return(0);
	}
	while (i < map.l_map)
	{
		ft_putendl(map.board[i]);
		i++;
	}
	return (0);
}
