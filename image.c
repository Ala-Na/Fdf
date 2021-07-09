/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 20:26:13 by anadege           #+#    #+#             */
/*   Updated: 2021/07/10 00:15:03 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_default_color(t_param *param, int i, int j)
{
	char			*pixel;
	unsigned int	default_color;

	if (i >= 0 && i < param->img_length && j >= 0 && j < param->img_height)
	{
		pixel = param->img_addr + (j * param->size_line)
			+ (i * param->bits_per_pixel / 8);
		default_color = mlx_get_color_value(param->mlx, param->default_color);
		*pixel = default_color;
	}
}

void	re_manage_image(t_param *param)
{
	void	*old_img;

	old_img = param->img;
	param->img = mlx_new_image(param->mlx, param->img_length, param->img_height);
	if (param->img == NULL)
	{
		param->img = old_img;
		ft_putstr_fd("\nMODIFICATION OF IMAGE ERROR\n\n", 1);
		return ;
	}
	param->img_addr = mlx_get_data_addr(param->img, &(param->bits_per_pixel),
			&(param->size_line), &(param->endian));
	draw_grid(param);
	if (old_img != NULL)
		mlx_destroy_image(param->mlx, old_img);
	mlx_put_image_to_window(param->mlx, param->window, param->img, 10, 10);
}

void	manage_image(t_param *param)
{
	param->img_addr = mlx_get_data_addr(param->img, &(param->bits_per_pixel),
			&(param->size_line), &(param->endian));
	draw_grid(param);
	mlx_put_image_to_window(param->mlx, param->window, param->img, 10, 10);
}
