/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:25:13 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/25 16:53:44 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char		is_valid_char(char c)
{
	return (c == '.' || c == '#');
}

TETRO		*decode_tetrominos(char *file)
{
	t_list		*tetrominos;
	int			fd;
	char		*lines[TETRO_SIZE];
	int			i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = 0;
	while (i < TETRO_SIZE)
	{
		get_next_line(fd, &(lines[i]));
		if (get_next_line(fd, &(lines[i])) == -1)
		{
			ft_array_strdel(&lines);
			return (NULL);
		}
	}

}
