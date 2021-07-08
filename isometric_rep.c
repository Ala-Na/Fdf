/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_rep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 22:36:32 by anadege           #+#    #+#             */
/*   Updated: 2021/07/08 15:40:37 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Function to convert any 3D x/y/z coordinates into 2D coordinates i/j with an
** isometric representation according to an alpha angle along the x axis. Alpha is set to 30 
** degree as default but can be modified to have a rotation effect. 
** Coordinates are multipled by the number of pixels per segment.
** Then the new coordinates are placed inside the windows limits.
*/
void	two_dim_iso_coordinates(t_param *param, t_point *point)
{
	double	i;
	double	j;
	double	alpha;
	double	radian;

	alpha = param->alpha;
	radian = PI / 180;
	i = (point->x * cos(alpha * radian) + point->y * cos((alpha + 120) * radian) + point->z * cos((alpha - 120) * radian)) * param->pix_per_seg;
	j = (point->x * sin(alpha * radian) + point->y * sin((alpha + 120) * radian) + point->z * sin((alpha - 120) * radian)) * param->pix_per_seg;
	i += (double)param->i_start;
	j += (double)param->j_start;
	point->i = (int)i;
	point->j = (int)j;
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
		if (prev_point->i != -1 && prev_point->j != -1)
				if (brasenham_segment(param, prev_point, curr_point) != 0)
					return (1);
		prev_point->i = -1;
		prev_point->j = -1;
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
		if (prev_point->i != -1 && prev_point->j != -1)
				if (brasenham_segment(param, prev_point, curr_point) != 0)
					return (1);
		prev_point->i = -1;
		prev_point->j = -1;
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

int	error_while_draw(t_point *prev_point, t_point *curr_point)
{
	free(prev_point);
	free(curr_point);
	return (1);
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
		return (1);
	}
	init_point(prev_point);
	init_point(curr_point);
	if (prep_horizontals_lines(param, prev_point, curr_point) != 0)
		return (error_while_draw(prev_point, curr_point));
	init_point(prev_point);
	init_point(curr_point);
	if (prep_verticals_lines(param, prev_point, curr_point) != 0)
		return (error_while_draw(prev_point, curr_point));
	free(prev_point);
	free(curr_point);
	return (0);
}

