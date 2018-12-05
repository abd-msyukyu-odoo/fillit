/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 17:17:48 by rhunders          #+#    #+#             */
/*   Updated: 2018/12/05 13:08:16 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	init_tetro(TETRO *piece)
{
	if (!piece)
		return ;
	init_coord(&piece->origin);
	init_coord(&piece->footprint);
}

void	init_coord(COORD *point)
{
	if (!point)
		return ;
	point->x = 0;
	point->y = 0;
}

void	init_check(CHECK *check)
{
	if (!check)
		return ;
	check->x = 0;
	check->y = 0;
	check->index = 0;
}

int		init_map(MAP *map, int *try, BOX *box)
{
	int		i;
	int		size;

	i = 0;
	size = box->nb_tetro * TETRO_SIZE;
	init_coord(&(map->start));
	map->dead_size = 0;
	while ((*try && (*try)--) || map->l_map * map->l_map < size)
		map->l_map += 1;
	if (map->board)
		ft_array_strdel(&map->board);
	if (!(map->board = (char**)malloc(sizeof(char*) * (map->l_map + 1))))
		return (-1);
	map->board[map->l_map] = NULL;
	while (i < map->l_map)
	{
		if (!(map->board[i] = (char*)malloc(sizeof(char) * (map->l_map + 1))))
		{
			ft_array_strdel(&map->board);
			return (-1);
		}
		ft_memset((void*)map->board[i], '.', map->l_map);
		map->board[i++][map->l_map] = 0;
	}
	return (1);
}
