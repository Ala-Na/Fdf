/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_rep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 22:36:32 by anadege           #+#    #+#             */
/*   Updated: 2021/07/06 20:52:44 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Function to convert any 3D x/y/z coordinates into 2D coordinates i/j with an
** isometric representation according to an alpha angle along the x axis. Alpha is set to 30 
** degree as default but can be modified to have a rotation effect. Then the new coordinates 
** are placed inside the windows limits.
*/
void	two_dim_iso_coordinates(t_param *param, t_point *point)
{
	double	i;
	double	j;
	double	alpha;
	double	radian;

	alpha = param->alpha;
	radian = PI / 180;
	// Obtain coordinates by calculus in a 2D environment
	i = point->x * cos(alpha * radian) + point->y * cos((alpha + 120) * radian) + point->z * cos((alpha - 120) * radian);
	j = point->x * sin(alpha * radian) + point->y * sin((alpha + 120) * radian) + point->z * sin((alpha - 120) * radian);
	printf("i is %f, j is %f\n", i, j);
	// Replace point with center of the image as center
	i += (double)param->i_start;
	j += (double)param->j_start;
	printf("after start i is %f j is %f\n", i, j);
	// Make it bigger accoriding to pix_per_seg
	i += (point->x + point->y) * (double)param->pix_per_seg;
	j += (point->x + point->y) * (double)param->pix_per_seg;
	//printf("after pix per seg i is %f j is %f\n", i, j);
	// Stock result
	point->i = (int)i;
	point->j = (int)j;
	print_point(point);
	printf("\n");
}

void	recup_three_dim_z(t_param *param, t_point *point)
{
	int	z;

	z = param->map_infos->lines_content[point->x + point->y * param->map_infos->lines_size];
	point->z = z;
}

int	prep_horizontals_lines(t_param *param, t_point *prev_point, t_point *curr_point)
{
	curr_point->y = 0;
	while (curr_point->y < param->map_infos->nbr_total_lines)
	{
		curr_point->x = 0;
		while (curr_point->x < param->map_infos->lines_size)
		{
			recup_three_dim_z(param, curr_point);
			two_dim_iso_coordinates(param, curr_point);
			if (prev_point->i != -1 && prev_point->j != -1)
				brasenham_segment(param, prev_point, curr_point);
			*prev_point = *curr_point;
			curr_point->x += 1;
		}
		*prev_point = *curr_point;
		curr_point->y += 1;
	}
	return (0);
}

int	prep_verticals_lines(t_param *param, t_point *prev_point, t_point *curr_point)
{
	curr_point->x = 0;
	while (curr_point->x < param->map_infos->lines_size)
	{
		curr_point->y = 0;
		while (curr_point->y < param->map_infos->nbr_total_lines)
		{
			recup_three_dim_z(param, curr_point);
			two_dim_iso_coordinates(param, curr_point);
			if (prev_point->i != -1 && prev_point->j != -1)
				brasenham_segment(param, prev_point, curr_point);
			*prev_point = *curr_point;
			curr_point->y += 1;
		}
		*prev_point = *curr_point;
		curr_point->x += 1;
	}
	return (0);
}

void	init_point(t_point *point)
{
	point->x = -1;
	point->y = -1;
	point->z = -1;
	point->i = -1;
	point->j = -1;
}

int	init_recup_three_dim_coordinates(t_param *param)
{
	t_point	*prev_point;
	t_point	*curr_point;

	prev_point = malloc(sizeof(*prev_point));
	curr_point = malloc(sizeof(*curr_point));
	if (!prev_point || !curr_point)
	{
		if (prev_point)
			free(prev_point);
		if (curr_point)
			free(curr_point);
		return (-1);
	}
	init_point(prev_point);
	init_point(curr_point);
	prep_horizontals_lines(param, prev_point, curr_point);
	init_point(prev_point);
	init_point(curr_point);
	prep_verticals_lines(param, prev_point, curr_point);
	free(prev_point);
	free(curr_point);
	return (0);
}

