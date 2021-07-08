/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjustments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 22:54:52 by anadege           #+#    #+#             */
/*   Updated: 2021/07/08 23:45:37 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Function to seek the minimum value of i or j (depending if values is 
** param->points->i or param->points->j) and return it as a positive value.
** This will be the "starting value" of i / j and will be added to each points
** before drawing.
*/
int	adjust_start(t_param *param, int *values)
{
	int max_position;
	int	value_min;
	int	position;

	if (!values)
		return (0);
	max_position = param->map_infos->nbr_total_lines * param->map_infos->lines_size;
	value_min = 0;
	position = 0;
	while (position < max_position)
	{
		if (values[position] < value_min)
			value_min = values[position];
		position++;
	}
	return (-value_min);
}

/*
** Function to seek the minimum value of i or j (depending if values is 
n** param->points->i or param->points->j) without the starting point added.
** This will be useful to seek the biggest value of pixels per segment which 
** will fit inside a window.
*/
int	seek_maximum_value(t_param *param, int *values)
{
	int max_position;
	int	value_max;
	int position;

	if (!values)
		return (0);
	max_position = param->map_infos->nbr_total_lines * param->map_infos->lines_size;
	value_max = 0;
	position = 0;
	while (position < max_position)
	{
		if (values[position] > value_max)
			value_max = values[position];
		position++;
	}
	return (value_max);
}

/*
** Function to seek the biggest pixels per segment value which can fit inside
** a window.
*/
int	adjust_pixel_per_segment(t_param *param)
{
	int	pix_per_seg;
	int	max_i;
	int max_j;

	pix_per_seg = 1;
	max_i = seek_maximum_value(param, param->points->i) + param->i_start;
	max_j = seek_maximum_value(param, param->points->j) + param->j_start;
	if (max_i == max_j && max_i == 0)
		return (1);
	while (max_i * (pix_per_seg + 1) < param->img_length
			&& max_j * (pix_per_seg + 1) < param->img_height)
		pix_per_seg++;
	return (pix_per_seg);
}
