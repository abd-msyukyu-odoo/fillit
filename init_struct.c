/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 17:17:48 by rhunders          #+#    #+#             */
/*   Updated: 2018/12/19 14:26:39 by dabeloos         ###   ########.fr       */
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
	piece->previous = NULL;
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
	while ((*try && (*try)--) || map->l_map * map->l_map < size)
		map->l_map += 1;
	map->max_dead_size = map->l_map * map->l_map - size;
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
	if (map && map->board)
		ft_array_strdel(&map->board);
}
