/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 17:57:12 by rhunders          #+#    #+#             */
/*   Updated: 2018/11/01 18:35:46 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>
#include <time.h>

int			fill_pattern(MAP *map, TETRO *piece, int index, COORD point)
{
	int		i;
	COORD	pos;

	i = 0;
	point.x -= piece->footprint.x;
	point.y -= piece->footprint.y;
	piece->origin = point;
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
	int i;
	int count;
	int diff;

	diff = map->size - (nb_tetro * TETRO_SIZE);
	count = 0;
	i = 0;
	while (i < map->l_map)
		if (map->board[y][i++] == '.')
			count++;
	if ((i = 0) || (y + 1 < map->l_map && map->space[y + 1]))
		while (i < y)
			map->tot += map->space[i++];
	if ((map->tot + count) > diff)
		return (0);
	map->space[y] = count;
	map->tot = 0;
	return (1);
}

static int	fillit(BOX *box, MAP *map, int index, int try, int acc)
{
	COORD			point;
	int				i;
	int				i2;

	i2 = 0;
	i = 0;
	if (index == box->nb_tetro)
		while ((i2 || (i2 = index == box->nb_tetro)) && i <= box->nb_tetro)
			if ((i == box->nb_tetro) || !map->rest[i++])
				return (i == box->nb_tetro);
	if ((i = 0) || (try == 1 && init_map(map, &try, box) == -1))
		return (0);
	if (map->rest[index])
	{
		map->tot = 0;
		while (i < map->l_map)
			if (!v_line (map, box->nb_tetro, i++))
				return (0);
		return (fillit(box, map, index + 1, 0, acc + 1));
	}
	point = box->tetro_box[index]->footprint;
	while (point.y < map->l_map)
	{
		while (point.x < map->l_map)
		{
			if (fill_pattern(map, box->tetro_box[index], index, point))
			{
				map->rest[index] = 1;
				i = index + 1;
				if ((index + 1 == box->nb_tetro || map->rest[index + 1]) && !(i = 0))
					while (i < box->nb_tetro && map->rest[i])
						i++;
				if (fillit(box, map, i, 0, acc+1))
					return (1);
				map->rest[index] = 0;
				erase_pattern(map->board, *box->tetro_box[index], point);
			}
			point.x += 1;
		}
		point.x = box->tetro_box[index]->footprint.x;
		if (v_line (map, box->nb_tetro, point.y - box->tetro_box[index]->footprint.y))
			point.y += 1;
		else if ((i = index + 1 == box->nb_tetro) || fillit(box, map, index + 1, 0, acc + 1))
			return (!i);
		else
			break;
	}
	map->tot = 0;
	map->rest[index] = 0;
	return ((!index) ? fillit(box, map, 0, 1, acc + 1) : 0);
}



int			main(int arc, char **argv)
{
	BOX		*box;
	MAP		map;
	int		i;

	i = 0;
	map.board = NULL;
	map.l_map = 0;
	map.space = NULL;
	map.tot = 0;
	if (arc != 2)
		return (0);
	if (!(box = read_file(argv[1])))
	{
		ft_putendl("error");
		return (0);
	}
	if (!(map.rest = (int*)malloc(sizeof(int) * box->nb_tetro)))
		return (0);
	while (i < box->nb_tetro || (i = 0))
		map.rest[i++] = 0;
	if (!(fillit(box, &map, 0, 1, 0)))
	{
		ft_putendl("backtrack error");
		return (0);
	}
	while (i </*=*/ map.l_map)
	{
		//if (i != map.l_map)
			ft_putendl(map.board[i]);
		//else
		//	ft_putendl("finish");
		i++;
	}
	return (0);
}
