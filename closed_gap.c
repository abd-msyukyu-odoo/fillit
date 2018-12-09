/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_gap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:42:09 by dabeloos          #+#    #+#             */
/*   Updated: 2018/12/09 01:58:28 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	fill_gap(MAP *map, int x, int y)
{
	int	dead_size;

	map->board[y][x] = ':';
	dead_size = 1;
	if (map->max_clean < y)
		map->max_clean = y;
	if (y == map->max_clean && x > map->max_cleanx)
		map->max_cleanx = x;	
	if (y - 1 >= 0 && map->board[y - 1][x] == '.')
		dead_size += fill_gap(map, x, y - 1);
	if (y + 1 < map->l_map && map->board[y + 1][x] == '.')
		dead_size += fill_gap(map, x, y + 1);
	if (x - 1 >= 0 && map->board[y][x - 1] == '.')
		dead_size += fill_gap(map, x - 1, y);
	if (x + 1 < map->l_map && map->board[y][x + 1] == '.')
		dead_size += fill_gap(map, x + 1, y);
	return (dead_size);
}

#include <stdio.h>

void		clean_map(MAP *map, COORD point)
{
	while (point.y <= map->max_clean/*map->max_clean.y*/)
	{
		while (point.x < map->l_map/*map->max_clean.x*/)
		{
			if (map->board[point.y][point.x] == ':')
				map->board[point.y][point.x] = '.';
			point.x++;
		}
		point.x = 0;
		point.y++;
	}
}

void		check_gaps(MAP *map)
{
	COORD			p;
	int				dead_size;

	init_coord(&p);
	while (p.y < map->l_map)
	{
		p.x = 0;
		while (p.x < map->l_map)
		{
			if (map->board[p.y][p.x] == '.')
			{
				dead_size = fill_gap(map, p.x, p.y);
				map->dead_size += dead_size % TETRO_SIZE;
				if (map->max_clean == map->l_map - 1 && map->max_cleanx == map->l_map - 1)
					return (clean_map(map, p));
				//if ((dead_size % TETRO_SIZE))
				//{
				if (map->dead_size > map->max_dead_size)
					return (clean_map(map, p));
				//}
				if (!map->start.y && dead_size >= 4 && !map->start.x)
					map->start = p;
				map->board[p.y][p.x] = '.';
			}
			else if (map->board[p.y][p.x] == ':')
				map->board[p.y][p.x] = '.';
			p.x++;
		}
		p.y++;
	}
}
