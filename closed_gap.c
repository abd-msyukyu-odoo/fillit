/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_gap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:42:09 by dabeloos          #+#    #+#             */
/*   Updated: 2018/12/06 11:03:11 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	fill_gap(MAP *map, int x, int y)
{
	int		dead_size;

	map->board[y][x] = ':';
	dead_size = 1;
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

static void	clean_map(MAP *map)
{
	COORD			p;

	init_coord(&p);
	while (p.y < map->l_map)
	{
		p.x = 0;
		while (p.x < map->l_map)
		{
			if (map->board[p.y][p.x] == ':')
				map->board[p.y][p.x] = '.';
			++(p.x);
		}
		++(p.y);
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
				if (dead_size < TETRO_SIZE)
					map->dead_size += dead_size;
				else if (map->start.x == 0 && map->start.y == 0)
				{
					map->start.x = p.x;
					map->start.y = p.y;
				}
			}
			++(p.x);
		}
		++(p.y);
	}
	clean_map(map);
}
