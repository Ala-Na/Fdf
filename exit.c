/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:33:13 by anadege           #+#    #+#             */
/*   Updated: 2021/07/09 17:36:41 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_points(t_point *points)
{
	if (points != NULL)
	{
		if (points->i != NULL)
			free(points->i);
		if (points->j != NULL)
			free(points->j);
		free(points);
	}
}

void	clean_exit(t_param *param)
{
	free_points(param->points);
	if (param->mlx != NULL && param->window != NULL)
		mlx_destroy_window(param->mlx, param->window);
	if (param->mlx != NULL && param->img != NULL)
		mlx_destroy_image(param->mlx, param->img);
	if (param->mlx != NULL)
		mlx_destroy_display(param->mlx);
	if (param != NULL)
	{
		if (param->mlx != NULL)
			free(param->mlx);
		if (param->map_infos != NULL)
		{
			if (param->map_infos->lines_content != NULL)
				free(param->map_infos->lines_content);
			free(param->map_infos);
		}
		free(param);
	}
}
