/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brasenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:48:24 by anadege           #+#    #+#             */
/*   Updated: 2021/07/08 22:36:13 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_point(t_point *point, t_param *param)
{
	int max;
	int i;

	i = 0;
	max = param->map_infos->nbr_total_lines * param->map_infos->lines_size;
	while (i < max)
	 {
		printf("point i is %i, point j is %i\n", point->i[i], point->j[i]);
		i++;
	 }
}

/*
** Quick function to respect norm : Give the absolute value of delta and 
** it's sign.
*/

/*int	get_delta_and_sign(int start, int end, int *sign)
{
	int	delta;

	*sign = 1;
	delta = end - start;
	if (delta < 0)
	{
		delta *= -1;
		*sign *= -1;
	}
	return (delta);
}
*/
/*
** Brasenham algorithm from Wikipedia page (english).
** For respect of norm, the sign of delta_i is stocked inside delta_x, same goes
** for delta_j stocked inside delta_y.
*/
/*
int	brasenham_segment(t_param *param, t_point *start_point, t_point *end_point)
{
	t_point	delta;
	int		error;
	int		mult_error;

	delta.i = get_delta_and_sign(start_point->i, end_point->i, &delta.x);
	delta.j = get_delta_and_sign(start_point->j, end_point->j, &delta.y);
	error = delta.i - delta.j;
	while (end_point->i != start_point->i && end_point->j != start_point->j)
	{
		if (put_pixel_default_color(param, start_point->i, start_point->j) != 0)
			return (1);
		mult_error = 2 * error;
		if (mult_error >= -delta.j)
		{
			error -= delta.j;
			start_point->i += delta.x;
		}
		if (mult_error <= delta.i)
		{
			error += delta.i;
			start_point->j += delta.y;
		}
	}
	if (put_pixel_default_color(param, start_point->i, start_point->j) != 0)
		return (1);
	return (0);
}*/
