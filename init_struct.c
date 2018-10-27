/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:21:07 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/27 14:25:47 by dabeloos         ###   ########.fr       */
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

void	init_check(CHECK *checkin)
{
	checkin->x = 0;
	checkin->y = 0;
	checkin->index = 0;
}