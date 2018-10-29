/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 11:44:41 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/29 11:59:44 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static MAP		generate_map(TETRO **tetro_box, int size)
{
	if (size == -1)
	{
		size = 0;
		while (*tetro_box != NULL)
			size += TETRO_SIZE;

	}
}
