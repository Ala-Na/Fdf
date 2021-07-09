/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 21:49:10 by anadege           #+#    #+#             */
/*   Updated: 2021/07/08 22:49:51 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Functions to convert any 3D x/y/z coordinates into 2D coordinates i/j with an
** isometric representation according to an alpha angle along the x axis. Alpha is set to 30 
** degree as default but can be modified to have a rotation effect. 
** Coordinates are multipled by 100 in order to conserve their value as int and
** stocked inside array of int which are elements of structure t_point.
*/
void	two_dim_coordinates(t_point *point, t_param *param)
{
	double	i;
	double	j;
	double	alpha;
	double	radian;

	alpha = param->alpha;
	radian = PI / 180;
	i = (point->x * cos((alpha + 120) * radian) + point->y * cos((alpha) * radian) + point->z * cos((alpha - 120) * radian)) * 100;
	j = (point->x * sin((alpha + 120) * radian) + point->y * sin((alpha) * radian) + point->z * sin((alpha - 120) * radian)) * 100;
	point->i[point->position] = (int)i;
	point->j[point->position] = (int)j;
}

/*
** Function to browse 3D coordinates and obtain 2D ones. Elements i and j 
** of t_point struct will be filled accordingly thanks to two_dim_coordinates function.
*/
void	fill_array_of_points(t_point *point, t_param *param)
{
	int	max_position;

	max_position = param->map_infos->lines_size * param->map_infos->nbr_total_lines;
	point->x = 0;
	while (point->x < param->map_infos->nbr_total_lines && point->position < max_position)
	{
		point->y = 0;
		while (point->y < param->map_infos->lines_size && point->position < max_position)
		{
			point->z = param->map_infos->lines_content[point->position];
			two_dim_coordinates(point, param);
			point->y += 1;
			point->position += 1;
		}
		point->x += 1;
	}
}

/*
** Initialization of t_point structure. Only elements i and j (array of int)
** will be kept for further utilisation.  Elements x, y, z and position are 
** used to recuperate 3D coordinates inside the t_map structure before 2D
** transformation.
*/
int	init_point(t_point *point, t_param *param)
{
	int	size_of_arrays;

	size_of_arrays = param->map_infos->nbr_total_lines * param->map_infos->lines_size;
	point->position = 0;
	point->x = -1;
	point->y = -1;
	point->z = -1;
	point->i = malloc(sizeof(int) * size_of_arrays);
	if (!point->i)
		return (1);
	point->j = malloc(sizeof(int) * size_of_arrays);
	if (!point->j)
	{
		free(point->i);
		return (1);
	}
	return (0);
}

/*
** Initialization of recuperation of 3D coordinate to obtain 2D
** coordinates which will be stock in i and j elements of a t_point
** structure. Those elements must be freed later.
*/ 
t_point	*recup_coordinates(t_param *param)
{
	t_point	*point;

	point = malloc(sizeof(*point));
	if (!point || init_point(point, param) == 1)
	{
		if (point)
			free(point);
		return (NULL);
	}
	fill_array_of_points(point, param);
	return (point);
}
