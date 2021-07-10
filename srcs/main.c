/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 20:14:02 by elanna            #+#    #+#             */
/*   Updated: 2021/07/10 15:38:15 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Function to initiate value of the main structure t_param.
*/
t_param	*init_param(t_map *map)
{
	t_param	*param;

	param = malloc(sizeof(*param));
	if (!param)
		return (NULL);
	param->perspective = 0;
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
	param->default_color = BLUE;
	param->map_infos = map;
	param->points = recup_coordinates(param);
	if (param->points == NULL)
		return (NULL);
	apply_adjustments(param);
	return (param);
}

t_param	*fdf(t_map *map, char *filepath)
{
	t_param	*param;

	param = init_param(map);
	if (param == NULL)
		return (init_error("STRUCTURE", param));
	param->mlx = mlx_init();
	if (param->mlx == NULL)
		return (init_error("MINILIBX", param));
	param->window = mlx_new_window(param->mlx, WIN_LENGTH,
			WIN_HEIGHT, filepath);
	if (param->window == NULL)
		return (init_error("WINDOW", param));
	param->img = mlx_new_image(param->mlx, param->img_length,
			param->img_height);
	if (param->img == NULL)
		return (init_error("IMAGE", param));
	manage_image(param);
	mlx_key_hook(param->window, key_hook, param);
	mlx_loop(param->mlx);
	return (param);
}

/*
** Main. Check number of arguments before starting core of program.
*/
int	main(int argc, char **argv)
{
	t_param	*param;
	t_map	*map;

	if (argc != 2)
		return (error_in_arguments(argc));
	map = get_map_content(argv[1]);
	if (!map || map->lines_size == -1)
		return (error_while_parsing(map));
	param = fdf(map, argv[1]);
	if (param == NULL)
		return (1);
	clean_exit(param);
	return (0);
}
