/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:39:27 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/31 19:44:15 by rhunders         ###   ########.fr       */
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
# define CHECK t_check_input
# define BOX t_tetro_box

typedef struct			s_2d_coordinates
{
	int					x;
	int					y;
}						t_2d_coordinates;

typedef struct			s_tetromino
{
	t_2d_coordinates	origin;
	t_2d_coordinates	footprint;
	t_2d_coordinates	pattern[TETRO_SIZE];
}						t_tetromino;

typedef struct			s_map
{
	char				**board;
	int					l_map;
	int					size;
	int					*space;
	int					*rest;
	int					tot;
}						t_map;

typedef struct			s_check_input
{
	int					x;
	int					y;
	int					index;
}						t_check_input;

typedef struct			s_tetro_box
{
	TETRO				**tetro_box;
	int					nb_tetro;
}						t_tetro_box;
void					init_check(CHECK *index);
void					init_tetro(TETRO *piece);
void					init_coord(COORD *point);
TETRO					*flood_fill(char **tetro_in);
BOX						*read_file(char *file);
int						init_map(MAP *map, int *try, BOX *box);

#endif
