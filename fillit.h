/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:39:27 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/25 16:32:22 by dabeloos         ###   ########.fr       */
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

typedef struct			s_2d_coordinates
{
	int					x;
	int					y;
}						t_2d_coordinates;

typedef struct			s_tetromino
{
	t_2d_coordinates	*origin;
	t_2d_coordinates	*footprint;
	t_2d_coordinates	**pattern;
}						t_tetromino;

typedef struct			s_map
{
	char				**board;
	int					size;
}						t_map;
#endif
