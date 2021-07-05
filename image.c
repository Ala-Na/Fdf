/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 20:26:13 by anadege           #+#    #+#             */
/*   Updated: 2021/07/05 21:11:25 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	put_pixel_default_color(t_param *param, int i, int j)
{
	char	*pixel;
	unsigned int default_color;

	pixel = param->img_addr + (j + param->size_line + i * (param->bits_per_pixel / 8));
	default_color = mlx_get_color_value(param->mlx, param->default_color);
	*(pixel) = default_color;
}

int	manage_image(t_param *param)
{
	param->img_addr = mlx_get_data_addr(param->img, &(param->bits_per_pixel), &(param->size_line), &(param->endian));
	printf("bits_per_pixel : %i, size_line : %i, endian : %i\n", param->bits_per_pixel, param->size_line, param->endian);
	return (init_recup_three_dim_coordinates(param));
}
