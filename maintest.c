/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 16:52:01 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/28 17:47:19 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define tp tetro->pattern[i]
#define to tetro->origin
#define tf tetro->footprint
#include "fillit.h"
#include <stdio.h>
int main()
{
	char **tab;
	char *str = "....$##..$.#..$.#..$";
	TETRO *tetro;
	int i = -1;

	tab = ft_strsplit(str,'$');
	tetro = flood_fill(tab);
	if (!tetro)
	{
		printf("NULL\n");
		return(0);
	}
	printf("o_x = %d\no_y = %d\nfootx %d\nfooty %d\n", to.x, to.y, tf.x, tf.y);
	while (++i < 4)
		printf("patt%d:\nx : %d\ny : %d\n", i, tp.x,tp.y);
	while (*tab)
	{
		printf("%s\n",*tab);
		tab++;
	}
}
