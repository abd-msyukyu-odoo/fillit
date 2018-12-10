/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:25:13 by dabeloos          #+#    #+#             */
/*   Updated: 2018/12/07 17:11:04 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		init_tetro_box(BOX *box, int index)
{
	if (!(box->tetro_box = (TETRO **)malloc(sizeof(TETRO *) * (index + 2))))
		return (0);
	box->tetro_box[index + 1] = NULL;
	box->nb_tetro = index + 1;
	return (1);
}

static char		check_tetro_read(char *tetro_read)
{
	size_t		i;
	int			count_hash;
	int			index_line;

	i = -1;
	count_hash = 0;
	index_line = 0;
	while (++i < (TETRO_SIZE + 1) * TETRO_SIZE)
	{
		if ((i + 1) % (TETRO_SIZE + 1) == 0)
		{
			if (tetro_read[i] != '\n' || index_line != TETRO_SIZE)
				return (0);
			index_line = 0;
			continue ;
		}
		else if (tetro_read[i] != '#' && tetro_read[i] != '.')
			return (0);
		if (tetro_read[i] == '#' && ++count_hash > TETRO_SIZE)
			return (0);
		if (++index_line > TETRO_SIZE)
			return (0);
	}
	return (count_hash == TETRO_SIZE);
}

static void		simplify_tetro(TETRO *tetro)
{
	int			i;

	tetro->footprint.x -= tetro->origin.x;
	tetro->footprint.y -= tetro->origin.y;
	i = -1;
	tetro->id = 0;
	while (++i < TETRO_SIZE)
	{
		tetro->pattern[i].x -= tetro->origin.x;
		tetro->pattern[i].y -= tetro->origin.y;
		tetro->id |=
			(1 << (TETRO_SIZE * tetro->pattern[i].y)) << tetro->pattern[i].x;
	}
	tetro->origin.x = 0;
	tetro->origin.y = 0;
}

static BOX		*read_tetro(int fd, BOX *box, int index)
{
	char			tetro_read[(TETRO_SIZE + 1) * TETRO_SIZE];
	ssize_t			nread;
	TETRO			*current;

	if (read(fd, tetro_read, (TETRO_SIZE + 1) * TETRO_SIZE) !=
	(TETRO_SIZE + 1) * TETRO_SIZE || !check_tetro_read(tetro_read) ||
	!(current = flood_fill(ft_strsplit(tetro_read, '\n'))) || index == 26)
		return (NULL);
	simplify_tetro(current);
	if (!(nread = read(fd, tetro_read, 1)))
	{
		if (!init_tetro_box(box, index))
			return (NULL);
	}
	else if ((nread == 1 && tetro_read[0] == '\n') || (box = NULL))
		box = read_tetro(fd, box, index + 1);
	if (!box)
	{
		free(current);
		return (NULL);
	}
	box->tetro_box[index] = current;
	return (box);
}

BOX				*read_file(char *file)
{
	BOX			*box;
	BOX			*tmp;
	int			fd;

	box = (BOX*)malloc(sizeof(BOX));
	if (!box)
		return (NULL);
	box->tetro_box = NULL;
	box->nb_tetro = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!(tmp = read_tetro(fd, box, 0)))
	{
		free(box);
		return (NULL);
	}
	close(fd);
	link_brothers(box);
	return (box);
}
