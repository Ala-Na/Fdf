/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 20:14:02 by elanna            #+#    #+#             */
/*   Updated: 2021/07/08 23:37:21 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_fdf(t_param *param)
{
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

int	key_hook(int keycode, t_param *param)
{
	if (keycode == 65307)
	{
		exit_fdf(param);
		exit(0);
		return (1);
	}
	return (0);
}

void	init_param(t_param *param, t_map *map)
{
	param->mlx = NULL;
	param->window = NULL;
	param->img = NULL;
	param->img_addr = NULL;
	param->bits_per_pixel = -1;
	param->size_line = -1;
	param->endian = -1;
	param->win_length = WIN_LENGTH;
	param->win_height = WIN_HEIGHT;
	param->img_length = param->win_length - 20;
	param->img_height = param->win_height - 20;
	param->alpha = ALPHA;
	param->default_color = WHITE;
	param->map_infos = map;
	param->points = recup_coordinates(param);
	param->pix_per_seg = 1;
	param->i_start = adjust_start(param, param->points->i);
	param->j_start = adjust_start(param, param->points->j);
	param->pix_per_seg = adjust_pixel_per_segment(param);
}

t_param	*init_fdf(t_map *map, char	*filepath)
{
	t_param	*param;
	int		image_done;

	param = malloc(sizeof(*param));
	if (!param)
		return (NULL);
	init_param(param, map);
	param->mlx = mlx_init();
	if (param->mlx == NULL)
	{
		ft_putstr_fd("Initiation error\n", 1);
		exit_fdf(param);
		return (NULL);
	}
	ft_putstr_fd("Initiation successful\n", 1);
	param->window = mlx_new_window(param->mlx, WIN_LENGTH, WIN_HEIGHT, filepath);
	param->img = mlx_new_image(param->mlx, param->img_length, param->img_height);
	if (param->window != NULL && param->img != NULL)
	{
		ft_putstr_fd("Window and image successfuly generated\n", 1);
		if (param->points == NULL)
		{
			ft_putstr_fd("Error while converting points\n", 1);
			return (NULL);
		}
		/*image_done = manage_image(param);
		if (image_done == 0)
			mlx_put_image_to_window(param->mlx, param->window, param->img, 20, 20);
		else
		{
			ft_putstr_fd("Error while drawing image\n", 1);
			exit_fdf(param);
			return (NULL);
		}*/
		mlx_key_hook(param->window, key_hook, param);
		mlx_loop(param->mlx);
	}
	else
	{
		ft_putstr_fd("Window or image error\n", 1);
		exit_fdf(param);
		return (NULL);
	}
	return (param);
}

int	main(int argc, char **argv)
{
	t_param	*param;
	t_map	*map;

	if (argc != 2)
		return (error_in_arguments(argc));
	map = get_map_content(argv[1]);
	if (!map || map->lines_size == -1)
		return (error_while_parsing(map));

	/*
	** Print map for test purpose only
	*/
	int i = 1;
	while (i <= (map->lines_size * map->nbr_total_lines))
	{
		printf("%4i", map->lines_content[i - 1]);
		if (i % map->lines_size == 0)
			printf("\n");
		i++;
	}
	printf("\n");
	/*
	** End test purpose
	*/

	param = init_fdf(map, argv[1]);
	if (param == NULL)
		return (1);
	return (0);
}
