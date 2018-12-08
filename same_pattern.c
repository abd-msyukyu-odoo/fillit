/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   same_pattern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:15:52 by dabeloos          #+#    #+#             */
/*   Updated: 2018/12/07 18:22:49 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				list_brothers(BOX *box)
{
	int		i;
	int		j;

	i = -1;
	while (++i < box->nb_tetro)
	{
		j = -1;
		while (++j < i)
			if (box->tetro_box[i]->id == box->tetro_box[j]->id)
				box->tetro_box[i]->brothers = box->tetro_box[j]->brothers;
		if (j == i && !(box->tetro_box[i]->brothers = search_brothers(box, i)))
			return (0);
	}
	return (1);
}
