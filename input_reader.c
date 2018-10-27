/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:25:13 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/27 17:42:57 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static char		is_valid_char(char c)
{
	return (c == '.' || c == '#');
}

static char		check_tetro_read(char *tetro_read)
{
	size_t		i;
	int			count_hash;
	int			index_line;

	i = -1;
	count_hash = 0;
	index_line = 0;
	while (tetro_read[++i] != '\0')
	{
		if ((i + 1) % (TETRO_SIZE + 1) == 0)
		{
			if (tetro_read[i] != '\n')
				return (0);
			if (index_line != TETRO_SIZE)
				return (0);
			index_line = 0;
			continue ;
		}
		else if(!is_valid_char(tetro_read[i]))
			return (0);
		if (tetro_read[i] == '#' && ++count_hash > TETRO_SIZE)
			return (0);
		if (++index_line > TETRO_SIZE)
			return (0);
	}
	return (1);
}

static void		simplify_tetro(TETRO *tetro)
{
	int			i;

	tetro->footprint.x -= tetro->origin.x;
	tetro->footprint.y -= tetro->origin.y;
	i = -1;
	while (++i < TETRO_SIZE)
	{
		tetro->pattern[i].x -= tetro->origin.x;
		tetro->pattern[i].y -= tetro->origin.y;
	}
	tetro->origin.x = 0;
	tetro->origin.y = 0;
}

static TETRO	**read_tetro(int fd, TETRO **tetro_box, int index)
{
	char			tetro_read[(TETRO_SIZE + 1) * TETRO_SIZE + 1];
	ssize_t			nread;
	TETRO			*current;

	nread = read(fd, tetro_read, (TETRO_SIZE + 1) * TETRO_SIZE);
	if (nread != (TETRO_SIZE + 1) * TETRO_SIZE)
		return (NULL);
	tetro_read[nread] = '\0';
	if (!check_tetro_read(tetro_read))
		return (NULL);
	current = flood_fill(ft_strsplit(tetro_read, '\n'));
	if (!current)
		return (NULL);
	simplify_tetro(current);
	nread = read(fd, tetro_read, 1);
	if (nread == 0)
	{
		tetro_box = (TETRO **)malloc(sizeof(TETRO *) * (index + 2));
		tetro_box[index + 1] = NULL;
	}
	else if (nread != 1 || tetro_read[0] != '\n')
	{
		free(current);
		return (NULL);
	}
	else
		tetro_box = read_tetro(fd, tetro_box, index + 1);
	if (tetro_box == NULL)
	{
		free(current);
		return (NULL);
	}
	tetro_box[index] = current;
	return (tetro_box);
}

TETRO			**read_file(char *file)
{
	TETRO			**tetro_box;
	int				fd;

	tetro_box = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	tetro_box = read_tetro(fd, tetro_box, 0);
	close(fd);
	return (tetro_box);
}
