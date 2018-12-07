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

void			list_brothers(BOX *box)
{
	int		i;
	TETRO	*current;

	i = 0;
	while (i < box->nb_tetro)
	{
		if (!box->tetro_box[i]->brothers)
		{
			//malloc list
		}
		else
		{

		}
	}
}
