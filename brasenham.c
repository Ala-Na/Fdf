/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brasenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:48:24 by anadege           #+#    #+#             */
/*   Updated: 2021/07/06 15:23:15 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_point(t_point *point)
{
	printf("Point is x %i y %i z %i and i %i j %i\n", point->x, point->y, point->z, point->i, point->j);
}


int	brasenham_segment(t_param *param, t_point *start_point, t_point *end_point)
{
	int	error_margin;
	int	delta_i;
	int	delta_j;

	error_margin = end_point->i - start_point->i;
	delta_i = error_margin * 2;
	delta_j = (end_point->j - start_point->j) * 2;
	put_pixel_default_color(param, start_point->i, start_point->j);
	while (start_point->i < end_point->i)
	{
		start_point->i += 1;
		error_margin -= delta_j;
		if (error_margin <= 0)
		{
			start_point->j += 1;
			error_margin += delta_i;
		}
		put_pixel_default_color(param, start_point->i, start_point->j);
	}
	return (0);
}
