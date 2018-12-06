/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 17:57:12 by rhunders          #+#    #+#             */
/*   Updated: 2018/12/06 11:44:51 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static COORD	get_start_coord(MAP *map, TETRO *piece)
{
	COORD	start;

	start.x = (map->start.x > piece->footprint.x) ? map->start.x :
		piece->footprint.x;
	start.y = (map->start.y > piece->footprint.y) ? map->start.y :
		piece->footprint.y;
	return (start);
}

static int		fill_pattern(MAP *map, TETRO *piece, int index, COORD point,
		int nb_tetro)
{
	int		i;

	i = 0;
	point.x -= piece->footprint.x;
	point.y -= piece->footprint.y;
	while (i < TETRO_SIZE || (i = 0))
		if (map->board[piece->pattern[i].y + point.y]
				[piece->pattern[i].x + point.x] != '.' || !++i)
			return (0);
	map->dead_size = 0;
	check_gaps(map);
	if (map->dead_size > map->l_map * map->l_map - nb_tetro * TETRO_SIZE)
		return (0);
	init_coord(&(map->start));
	while (i < TETRO_SIZE)
	{
		map->board[piece->pattern[i].y + point.y]
		[piece->pattern[i].x + point.x] = 'A' + index;
		i++;
	}
	return (1);
}

static int		erase_pattern(char **board, TETRO piece, COORD point)
{
	int index;

	index = TETRO_SIZE;
	point.x -= piece.footprint.x;
	point.y -= piece.footprint.y;
	while (--index > -1)
		board[piece.pattern[index].y + point.y]
			[piece.pattern[index].x + point.x] = '.';
	return (index);
}

static int		fillit(BOX *box, MAP *map, int index, int try)
{
	COORD			point;

	if (index == box->nb_tetro)
		return (1);
	if (try && init_map(map, &try, box) == -1)
		return (0);
	point = get_start_coord(map, box->tetro_box[index]);
	while (point.y < map->l_map)
	{
		while (point.x < map->l_map)
		{
			if (fill_pattern(map, box->tetro_box[index], index, point,
						box->nb_tetro))
			{
				if (fillit(box, map, index + 1, 0))
					return (1);
				erase_pattern(map->board, *box->tetro_box[index], point);
			}
			point.x += 1;
		}
		point.x = box->tetro_box[index]->footprint.x;
		point.y += 1;
	}
	return ((!index) ? fillit(box, map, 0, 1) : 0);
}

int				main(int argc, char **argv)
{
	BOX		*box;
	MAP		map;
	int		i;

	i = 0;
	map.board = NULL;
	map.l_map = 0;
	if (argc != 2)
	{
		ft_putendl("usage: ./fillit filename");
		return (0);
	}
	if (!(box = read_file(argv[1])) || !(fillit(box, &map, 0, 1)))
	{
		ft_putendl("error");
		return (0);
	}
	while (i < map.l_map)
	{
		ft_putendl(map.board[i]);
		i++;
	}
	return (0);
}
