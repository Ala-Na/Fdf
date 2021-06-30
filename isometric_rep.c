/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_rep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 22:36:32 by anadege           #+#    #+#             */
/*   Updated: 2021/06/30 11:55:03 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h> 

typedef struct s_map
{
	int	lines_size;
	int	nbr_total_lines;
	int	*lines_content;
}	t_map;

typedef struct	s_win_param
{
	int	width;
	int	height;
} t_win_param;

void	point_to_isometric(t_map map, s_win_param window)
{
	int	x_pnt;
	int	y_pnt;
	int	z_pnt;
	int	position;

	int	iso_up;
	int	iso_down;
	int	iso_left;
	int	iso_right;

	int	iso_x;
	int	iso_y;

	position = 0;
	x_pnt = 0;
	y_pnt = 0;
	z_pnt = map.lines_content[position];

	

	// Faire fonction récursives ?
	//Next point x axis
	if (x_pnt < map.lines_size)
		x_pnt += 1;
		position += 1;
		z_pnt = map.lines_content[position];

	//Next point y axis
	if (y_pnt < nbr_total_lines)
		y_pnt += 1;
		position += map.lines_size;
		z_pnt = map.lines_content[position];
}
