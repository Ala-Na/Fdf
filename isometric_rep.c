/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_rep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 22:36:32 by anadege           #+#    #+#             */
/*   Updated: 2021/07/05 12:05:38 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "fdf.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "fdf.h"

/*
** Function to convert any 3D x/y/z coordinates into 2D coordinates i/j with an
** isometric representation according to an alpha angle along the x axis. Alpha is set to 30 
** degree as default but can be modified to have a rotation effect.
*/
void	twod_iso_coordinates(t_param *param, t_point *point)
{
	double	i;
	double	j;
	double	alpha;
	double	radian;

	alpha = ALPHA;
	radian = PI / 180;
	// Obtain coordinates by calculus in a 2D environment
	i = point->x * cos(alpha * radian) + point->y * cos((alpha + 120) * radian) + point->z * cos((alpha - 120) * radian);
	j = point->x * sin(alpha * radian) + point->y * sin((alpha + 120) * radian) + point->z * sin((alpha - 120) * radian);
	// Replace point with center of the image as center
	i += (double)param->i_center;
	j += (double)param->j_center;
	// Stock result
	point->i = (int)i;
	point->j = (int)j;
}

void	recup_threed_z(t_param *param, t_point *point)
{
	int	z;

	z = param->map_infos->lines_content[point->x + point->y * param->map_infos->lines_size];
	point->z = z;

}

void	recup_threed_coordinates(t_param *param)
{
	int		x;
	int		y;
	int		z;
	t_point	*prev_point;
	t_point	*curr_point;

	// Vertical
	x = 0;
	while (x < param->map_infos->lines_size)
	{
		y = 0;
		while (y < param->map_infos->nbr_total_lines)
		{
			// get iso coordinate and draw segment ?
			y += 1;
		}
		x += 1;
	}

	//Horizontal
	y = 0;
	while (y < param->map_infos->nbr_total_lines)
	{
		x = 0;
		while (x < param->map_infos->lines_size)
		{
			z = param->map_infos->lines_content[x + y * param->map_infos->lines_size];
			// get iso coordinate and draw segment ?
			x += 1;
		}
		y += 1;
	}
}
