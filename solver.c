/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 17:57:12 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/29 17:39:57 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	fill_pattern(MAP *map, TETRO *piece, int index, COORD point)
{
	int		i;
	COORD	pos;

	i = 0;
	point.x -= piece->footprint.x;
	point.y -= piece->footprint.y;
	while (i < TETRO_SIZE)
	{
		pos.y = piece->pattern[i].y + point.y;
		pos.x = piece->pattern[i].x + point.x;
		if (map->board[pos.y][pos.x] == '.')
			map->board[pos.y][pos.x] = 'A' + index;
		else
		{
			while (--i > -1)
				map->board[piece->pattern[i].y + point.y]
					[piece->pattern[i].x + point.x] = '.';
			return (0);
		}
		i++;
	}
	return (1);
}

static int	erase_pattern(char **board, TETRO piece, int index, COORD point)
{
	point.x -= piece.footprint.x;
	point.y -= piece.footprint.y;
	while (--index > -1)
		board[piece.pattern[index].y + point.y]
			[piece.pattern[index].x + point.x] = '.';
	return (index);
}

static int	fillit(BOX *box, MAP *map, int index, int try)
{
	COORD			point;

	if (index == box->nb_tetro)
		return (1);
	if (try && init_map(map, &try, box) == -1)
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
					return (1);
				erase_pattern(map->board, *box->tetro_box[index], index, point);
			}
			point.x += 1;
		}
		point.x = box->tetro_box[index]->footprint.x;
		point.y += 1;
	}
	return ((!index) ? fillit(box, map, 0, 1) : 0);
}

int			main(int arc, char **argv)
{
	BOX		*box;
	MAP		map;
	int		i;

	i = 0;
	map.board = NULL;
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
		return (0);
	}
	while (i < map.l_map)
	{
		ft_putendl(map.board[i]);
		i++;
	}
	return (0);
}
