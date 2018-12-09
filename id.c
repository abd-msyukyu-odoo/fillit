/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 02:59:16 by rhunders          #+#    #+#             */
/*   Updated: 2018/12/09 05:46:05 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>
/*
int         check_id(BOX *box, int index, int i, int count)
{
	int same_id;

	same_id = 0;
	if (index == box->nb_tetro)
		return (1);
	while (++i < box->nb_tetro)
		if (i != index && box->tetro_box[i]->id == box->tetro_box[index]->id)
		{
			if (!check_id(box, index, i, count + 1))
				return (0);
			same_id = i;
			break;
		}
//	printf("index -> %d count -> %d\n", index, count);
	if (i == box->nb_tetro)
	{
		if (!count)
		{
			box->tetro_box[index]->index_sameid = NULL;
			return (check_id(box, index + 1, -1, 0));
		}
		else
		{
			if (!(box->tetro_box[index]->index_sameid = (int*)malloc(sizeof(int) * count)))
				return (0);
			box->tetro_box[index]->nb_sameid = count;
		}
		return (check_id(box, index + 1, -1, 0));
	}
	box->tetro_box[index]->index_sameid[count] = same_id;
	return (1);
}
*/
int         check_id(BOX *box, int index, int i, int count)
{
	int same_id;

	same_id = 0;
	if (index == box->nb_tetro)
		return (1);
	if (box->tetro_box[index]->start_sameid)
		return (check_id(box, index + 1, -1, 0));
	while (++i < box->nb_tetro)
		if (i != index && box->tetro_box[i]->id == box->tetro_box[index]->id)
		{
			if (!check_id(box, index, i, count + 1))
				return (0);
				box->tetro_box[i]->start_sameid = box->tetro_box[index]->start_sameid;
			same_id = i;
		}
	if (i == box->nb_tetro)
	{
		if (count && !box->tetro_box[index]->start_sameid)
		{
			if (!(box->tetro_box[index]->start_sameid = (COORD*)malloc(sizeof(COORD))))
				return (0);
			*box->tetro_box[index]->start_sameid = box->tetro_box[index]->footprint;
		}
		return (check_id(box, index + 1, -1, 0));
	}
	return (1);
}

COORD		ft_biggest_point(COORD point1, COORD point2)
{
	if (point1.y > point2.y || (point1.y == point2.y && point1.x > point2.x))
		return (point1);
	return (point2);
}
