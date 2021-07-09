/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   representation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 11:22:28 by anadege           #+#    #+#             */
/*   Updated: 2021/07/09 22:48:50 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Sub-function for brasenham segment to calculate the delta of i or j, and it's sign.
*/
int	get_delta_and_sign(int start_value, int end_value, int	*sign)
{
	int	delta;

	delta = end_value - start_value;
	if (delta < 0)
	{
		delta *= -1;
		*sign = -1;
	}
	else
		*sign = 1;
	return (delta);
}

/*
** Brasenham algorithm from Wikipedia page (english) to calculate pixels
** position between two points.
** For respect of norm, variables needed by this function are stocked
** inside a special t_brasenham structure.
** Each point/pixel of the segment is put inside the image.
*/
void	brasenham_segment(t_param *param, int start, int end)
{
	t_brasenham	bra;

	bra.i_start = param->points->i[start];
	bra.i_end = param->points->i[end];
	bra.j_start = param->points->j[start];
	bra.j_end = param->points->j[end];
	bra.delta_i = get_delta_and_sign(bra.i_start, bra.i_end, &bra.sign_i);
	bra.delta_j = get_delta_and_sign(bra.j_start, bra.j_end, &bra.sign_j);
	bra.error = bra.delta_i - bra.delta_j;
	while (bra.i_start != bra.i_end || bra.j_start != bra.j_end)
	{
		put_pixel_default_color(param, bra.i_start, bra.j_start);
		bra.mult_error = 2 * bra.error;
		if (bra.mult_error >= -(bra.delta_j))
		{
			bra.error -= bra.delta_j;
			bra.i_start += bra.sign_i;
		}
		if (bra.mult_error <= bra.delta_i)
		{
			bra.error += bra.delta_i;
			bra.j_start += bra.sign_j;
		}
	}
	put_pixel_default_color(param, bra.i_start, bra.j_start);
}

/*
** Function to start drawing the grid representing the map. For each point,
** the segment with it's x+1 and y+1 values are draw thanks to brasenham algorithm.
*/
void	draw_grid(t_param *param)
{
	int	max_pos;
	int	curr_pos;
	int	next_i_pos;
	int	next_j_pos;

	max_pos = param->map_infos->nbr_total_lines * param->map_infos->lines_size;
	curr_pos = 0;
	while (curr_pos < max_pos)
	{
		next_i_pos = curr_pos + 1;
		next_j_pos = curr_pos + param->map_infos->lines_size;
		if ((curr_pos + 1) % param->map_infos->lines_size != 0
				&& curr_pos < max_pos)
			brasenham_segment(param, curr_pos, next_i_pos);
		if (next_j_pos < max_pos)
			brasenham_segment(param, curr_pos, next_j_pos);
		curr_pos += 1;
	}
}

