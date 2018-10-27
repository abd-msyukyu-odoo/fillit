/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:39:27 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/27 14:46:35 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# define COORD t_2d_coordinates
# define TETRO t_tetromino
# define MAP t_map
# define TETRO_SIZE 4
# define T_MAX 4 - 1
# define CHECK t_check_input

typedef struct			s_2d_coordinates
{
	int					x;
	int					y;
}						t_2d_coordinates;

typedef struct			s_map
{
	char				**board;
	int					size;
}						t_map;

typedef struct			s_check_input
{
	int					x;
	int					y;
	int					index;
}						t_check_input;

typedef struct			s_tetromino
{
	t_2d_coordinates	origin;
	t_2d_coordinates	footprint;
	t_2d_coordinates	pattern[TETRO_SIZE];
}						t_tetromino;
TETRO					*flood_fill(char **tetro_in);
void					init_tetro(TETRO *piece);
void					init_coord(COORD *point);
void					init_check(CHECK *checkin);
TETRO					**read_file(char *file);

#endif
