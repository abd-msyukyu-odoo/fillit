/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_gap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:42:09 by dabeloos          #+#    #+#             */
/*   Updated: 2018/12/19 14:31:57 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	fill_gap(MAP *map, int x, int y)
{
	int	dead_size;

	map->board[y][x] = ':';
	dead_size = 1;
	if (y - 1 >= 0 && map->board[y - 1][x] == '.')
		dead_size += fill_gap(map, x, y - 1);
	if (y + 1 < map->l_map && map->board[y + 1][x] == '.')
	{
		if (y + 1 > map->maxy_clean)
			map->maxy_clean = y + 1;
		dead_size += fill_gap(map, x, y + 1);
	}
	if (x - 1 >= 0 && map->board[y][x - 1] == '.')
	{
		if (x - 1 < map->tmp_start.x)
			map->tmp_start.x = x - 1;
		dead_size += fill_gap(map, x - 1, y);
	}
	if (x + 1 < map->l_map && map->board[y][x + 1] == '.')
		dead_size += fill_gap(map, x + 1, y);
	return (dead_size);
}

static void	clean_map(MAP *map, COORD p)
{
	while (p.y <= map->maxy_clean)
	{
		while (p.x < map->l_map)
		{
			if (map->board[p.y][p.x] == ':')
				map->board[p.y][p.x] = '.';
			p.x++;
		}
		p.x = 0;
		p.y++;
	}
}

void		check_gaps(MAP *map)
{
	COORD			p;
	int				dead_size;

	p.y = -1;
	while (++(p.y) < map->l_map)
	{
		p.x = -1;
		while (++(p.x) < map->l_map)
		{
			if (map->board[p.y][p.x] == '.')
			{
				if (p.y > map->maxy_clean)
					map->maxy_clean = p.y;
				map->tmp_start = p;
				dead_size = fill_gap(map, p.x, p.y);
				map->dead_size += dead_size % TETRO_SIZE;
				if (map->dead_size > map->max_dead_size)
					return (clean_map(map, p));
				if (!map->first && dead_size >= 4 && (map->first = 1))
					map->start = map->tmp_start;
			}
			if (map->board[p.y][p.x] == ':')
				map->board[p.y][p.x] = '.';
		}
	}
}
