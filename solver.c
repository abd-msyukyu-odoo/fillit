/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 17:57:12 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/31 16:17:25 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int			fill_pattern(MAP *map, TETRO *piece, int index, COORD point)
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

int			erase_pattern(char **board, TETRO piece, COORD point)
{
	int i;

	i = 0;
	point.x -= piece.footprint.x;
	point.y -= piece.footprint.y;
	while (i < TETRO_SIZE)
	{
		board[piece.pattern[i].y + point.y][piece.pattern[i].x + point.x] = '.';
		++i;
	}
	return (i);
}

static int v_line(MAP *map, int nb_tetro, int y)
{
	int count;
	int i;
	static int diff = 0;
	//static int iteration = 0;
	//static int nb_tet = 0;

	//printf ("y %d\niteration %d\ndiff %d\n", y, iteration, diff);
	if (!diff)
		if ((diff = (map->l_map * map->l_map) - (nb_tetro * TETRO_SIZE)) < 0);
		{
			diff = 0;
			return (0);
		}
	i = 0;
	count = 0;
	while (i < map->l_map)
		if (map->board[y][i++] == '.')
			count++;
	printf("count %d\ny %d\n", count, y);
	if (count > diff)
	{
		diff = count - diff;
		iteration++;
		return (1);
	}
	return (0);
	
}

static int	fillit(BOX *box, MAP *map, int index, int try)
{
	COORD			point;
	int				inc;

	inc = 1;
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
				if (fillit(box, map, index + inc, 0))
					return (1);
				erase_pattern(map->board, *box->tetro_box[index], point);
			}
			point.x += 1;
		}
		point.x = box->tetro_box[index]->footprint.x;
		//printf ("y backtrack %d\n", point.y);
		//if (v_line(map, box->nb_tetro, point.y))
		//{
			point.y += 1;
		/*}
		else if (fillit(box, map, index + 1, 0) && index != 0)
		{	
			printf("espace ok\n");
			return (1);
		}
		else
		{
			printf("argandir map\n");
			return (fillit(box, map, 0, 1));
		}*/
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
		ft_putendl("error");
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
