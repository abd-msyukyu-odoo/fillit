/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 17:17:48 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/28 23:39:22 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	init_tetro(TETRO *piece)
{
	init_coord(&piece->origin);
	init_coord(&piece->footprint);
}

void	init_coord(COORD *point)
{
	point->x = 0;
	point->y = 0;
}

void	init_check(CHECK *check)
{
	check->x = 0;
	check->y = 0;
	check->index = 0;
}

MAP		i_map()
{
	MAP map;

	map.board = NULL;
	map.size = 0;
	map.l_map = 0;
	return (map);
}
