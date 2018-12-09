/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 17:17:48 by rhunders          #+#    #+#             */
/*   Updated: 2018/12/09 05:50:23 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	init_tetro(TETRO *piece)
{
	if (!piece)
		return ;
	init_coord(&piece->origin);
	init_coord(&piece->footprint);
	piece->id = 0;
	piece->placed = 0;
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

#include <stdio.h>
#include <time.h>

int		init_map(MAP *map, int *try, BOX *box)
{
	int		i;
	int		size;

	i = 0;
	size = box->nb_tetro * TETRO_SIZE;
	init_coord(&(map->start));
	while ((*try && (*try)--) || map->l_map * map->l_map < size)
		map->l_map += 1;
	map->max_dead_size = map->l_map * map->l_map - size;
	
//	printf ("map->l_map -> %d\n" , map->l_map);
	//printf("max dead_size %d\n", map->max_dead_size);
	//clock_t time = clock();
	//while (time + CLOCKS_PER_SEC * 2 > clock())
	//	;
	if (map->board)
		ft_array_strdel(&map->board);
	if (!(map->board = (char**)malloc(sizeof(char*) * (map->l_map + 1))))
		return (-1);
	while (i < map->l_map || (map->dead_size = 0))
	{
		if (!(map->board[i] = (char*)malloc(sizeof(char) * (map->l_map + 1))))
		{
			ft_array_strdel(&map->board);
			return (-1);
		}
		ft_memset((void*)map->board[i], '.', map->l_map);
		map->board[i++][map->l_map] = 0;
	}
	map->board[i] = NULL;
	return (1);
}

void	mega_free(BOX *box, MAP *map)
{
	int i;

	i = 0;
	if (box && box->tetro_box)
	{
		while (i < box->nb_tetro || (i = 0))
			free(box->tetro_box[i++]);
		free(box->tetro_box);
		free(box);
	}
	//(void)map;
	if (map && map->board)
	{
		//while (i < map->l_map)
		//	free(map->board[i++]);
		//free(map->board);
		map->board[map->l_map] = NULL;
		ft_array_strdel(&map->board);
	}
	//	ft_array_strdel(&map->board);
}
