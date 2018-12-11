/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 17:17:48 by rhunders          #+#    #+#             */
/*   Updated: 2018/12/11 16:49:51 by rhunders         ###   ########.fr       */
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
	if (map->max_dead_size > (map->l_map * map->l_map) / 5)
		map->flag_gaps = 1;
	else
		map->flag_gaps = 0;
	while (i < map->l_map || (map->dead_size = 0))
	{
		ft_memset((void*)map->board[i], '.', map->l_map);
		map->board[i++][map->l_map] = 0;
	}
	return (1);
}

void	mega_free(BOX *box)
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
}
