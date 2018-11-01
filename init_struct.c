/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 17:17:48 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/31 21:40:02 by rhunders         ###   ########.fr       */
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

	i = 0;
	map->size = box->nb_tetro * TETRO_SIZE;
	while ((*try && (*try)--) || map->l_map * map->l_map < map->size)
		map->l_map += 1;
	if (map->board)
		ft_array_strdel(&map->board);
	map->size = map->l_map * map->l_map;
	//printf ("size %d\n",map->l_map * map->l_map);
	if (map->space)
		free(map->space);
	if (!(map->space = (int*)malloc(sizeof(int) * map->l_map)))
		return (-1);
	if (!(map->board = (char**)malloc(sizeof(char*) * (map->l_map + 1))))
		return (-1);
	map->board[map->l_map] = NULL;
	while (i < box->nb_tetro || (i = 0))
		map->rest[i++] = 0;
	while (i < map->l_map)
	{
		if (!(map->board[i] = (char*)malloc(sizeof(char) * (map->l_map + 1))))
		{
			ft_array_strdel(&map->board);
			return (-1);
		}
		ft_memset((void*)map->board[i], '.', map->l_map);
		map->board[i][map->l_map] = 0;
		map->space[i++] = 0;
	}
	return (1);
}
