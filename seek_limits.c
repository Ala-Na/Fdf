/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_limits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:31:40 by anadege           #+#    #+#             */
/*   Updated: 2021/07/07 17:45:37 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Approximation of potential max_i by taking into account max_x, max_y and max_z
** or min_z according to angle but those points may not be the same.
*/
int	seek_potential_max_i(t_param *param)
{
	double	max_i_max_z;
	double	max_i_min_z;
	int		alpha;
	double	radian;

	alpha = param->alpha;
	radian = PI / 180; 
	max_i_max_z = param->map_infos->lines_size * cos (alpha * radian) 
		+ param->map_infos->nbr_total_lines * cos ((alpha + 120) * radian)
		+ param->map_infos->max_z * cos ((alpha - 120) * radian);
	max_i_min_z = param->map_infos->lines_size * cos (alpha * radian) 
		+ param->map_infos->nbr_total_lines * cos ((alpha + 120) * radian)
		+ param->map_infos->min_z * cos ((alpha - 120) * radian);
	if (max_i_max_z < 0)
		max_i_max_z *= -1;
	if (max_i_min_z < 0)
		max_i_min_z *= -1;
	if (max_i_max_z > max_i_min_z)
		return ((int)max_i_max_z);
	else
		return ((int)max_i_min_z);
}

/*
** Approximation of potential max_i by taking into account max_x, max_y and max_z
** or min_z according to angle but those points may not be the same.
*/
int	seek_potential_max_j(t_param *param)
{
	double	max_j_max_z;
	double	max_j_min_z;
	int		alpha;
	double	radian;

	alpha = param->alpha;
	radian = PI / 180; 
	max_j_max_z = param->map_infos->lines_size * sin (alpha * radian) 
		+ param->map_infos->nbr_total_lines * sin ((alpha + 120) * radian)
		+ param->map_infos->max_z * sin ((alpha - 120) * radian);
	max_j_min_z = param->map_infos->lines_size * sin (alpha * radian) 
		+ param->map_infos->nbr_total_lines * sin ((alpha + 120) * radian)
		+ param->map_infos->min_z * sin ((alpha - 120) * radian);
	if (max_j_max_z < 0)
		max_j_max_z *= -1;
	if (max_j_min_z < 0)
		max_j_min_z *= -1;
	if (max_j_max_z > max_j_min_z)
		return ((int)max_j_max_z);
	else
		return ((int)max_j_min_z);
}

/*
** Ajust pix_per_seg (pixel per segment or distance between two coordinates)
** according to start point, limits of image, and supposed max i/max j. 
** Pix_per_seg can't be less than 4 pixels in order for line to still be visible.
*/
void	adjust_pixel_per_segment(t_param *param)
{
	int	max_i;
	int	max_j;

	max_i = seek_potential_max_i(param);
	max_j = seek_potential_max_j(param);
	while (param->pix_per_seg > 4 && ((max_i * param->pix_per_seg + param->i_start) > param->img_length
				|| (max_j * param->pix_per_seg + param->j_start) > param->img_height))
		param->pix_per_seg -= 1;
	param->pix_per_seg -= 1;
	param->pix_per_seg = 20;
	printf("Max i : %i Max j : %i\nPix_per_seg : %i\n", max_i, max_j, param->pix_per_seg);
}

/*
** Search minimum z coordinate in map.
*/
int	seek_min_z(t_map *map)
{
	int	min_z;
	int	i;

	min_z = 0;
	i = 0;
	while (i < map->lines_size * map->nbr_total_lines)
	{
		if (map->lines_content[i] < min_z)
			min_z = map->lines_content[i]; 
		i++;
	}
	return (min_z);
}

/*
** Search minimum z coordinate in map.
*/
int	seek_max_z(t_map *map)
{
	int	max_z;
	int	i;

	max_z = 0;
	i = 0;
	while (i < map->lines_size * map->nbr_total_lines)
	{
		if (map->lines_content[i] > max_z)
			max_z = map->lines_content[i]; 
		i++;
	}
	return (max_z);
}
