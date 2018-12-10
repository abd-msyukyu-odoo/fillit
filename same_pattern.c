/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   same_pattern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:15:52 by dabeloos          #+#    #+#             */
/*   Updated: 2018/12/10 13:42:38 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void				link_brothers(BOX *box)
{
	int		i;
	int		j;

	i = box->nb_tetro;
	while (--i >= 0)
	{
		j = i;
		while (--j >= 0)
			if (box->tetro_box[i]->id == box->tetro_box[j]->id)
			{
				box->tetro_box[i]->previous = box->tetro_box[j];
				break ;
			}
	}
}
