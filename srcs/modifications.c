/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 18:19:12 by anadege           #+#    #+#             */
/*   Updated: 2021/07/10 15:39:16 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	erase_modifications(t_param *param)
{
	t_point	*new_points;
	t_point	*old_points;

	old_points = param->points;
	new_points = recup_coordinates(param);
	if (new_points == NULL)
		return ;
	if (old_points != NULL)
		free_points(old_points);
	param->points = new_points;
	apply_adjustments(param);
	re_manage_image(param);
}

void	modify_perspective(t_param *param)
{
	t_point	*new_points;
	t_point	*old_points;

	if (param->perspective == 0)
	{
		old_points = param->points;
		param->perspective = 1;
		new_points = recup_coordinates(param);
		if (new_points == NULL)
		{
			param->perspective = 0;
			return ;
		}
		if (old_points != NULL)
			free_points(old_points);
		param->points = new_points;
		apply_adjustments(param);
		re_manage_image(param);
	}
	else
	{
		param->perspective = 0;
		erase_modifications(param);
	}
}

void	modify_position(t_param *param, int modif)
{
	int		max_position;
	int		ind;
	double	new_i;
	double	new_j;

	max_position = param->map_infos->nbr_total_lines
		* param->map_infos->lines_size;
	ind = 0;
	while (ind < max_position)
	{
		if (modif == 60 || modif == -60)
		{
			new_i = param->points->i[ind];
			new_j = param->points->j[ind] + modif;
		}
		else
		{
			new_i = param->points->i[ind] + (modif / 2);
			new_j = param->points->j[ind];
		}
		param->points->i[ind] = (int)new_i;
		param->points->j[ind] = (int)new_j;
		ind += 1;
	}
	re_manage_image(param);
}
