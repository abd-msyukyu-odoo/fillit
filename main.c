/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 17:28:08 by dabeloos          #+#    #+#             */
/*   Updated: 2018/12/19 14:26:42 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		main(int argc, char **argv)
{
	int			i;
	MAP			map;
	t_tetro_box	*box;

	map.board = NULL;
	map.l_map = 0;
	if (argc != 2)
	{
		ft_putendl("usage: ./fillit filename");
		return (0);
	}
	if (!(box = read_file(argv[1])) || !(fillit(box, &map, 0, 1)))
	{
		ft_putendl("error");
		mega_free(box, &map);
		return (0);
	}
	i = 0;
	while (i < map.l_map)
		ft_putendl(map.board[i++]);
	mega_free(box, &map);
	return (0);
}
