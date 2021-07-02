/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 20:14:02 by elanna            #+#    #+#             */
/*   Updated: 2021/07/02 15:43:03 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_param *param)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(param->mlx, param->window);
		mlx_destroy_display(param->mlx);
		free(param->mlx);
		free(param->map_infos->lines_content);
		free(param->map_infos);
		free(param);
		exit(0);
		return (1);
	}
	return (0);
}

t_param	*fill_param(t_map *map)
{
	t_param	*param;


}

t_param	*init_fdf(t_map *map, char	*filepath)
{
	t_param	*param;

	param = malloc(sizeof(*param));
	param->map_infos = map;
	param->mlx = mlx_init();
	if (param->mlx == NULL)
	{
		ft_putstr_fd("Initiation error\n", 1);
		param->valid = 0;
		return (param);
	}
	ft_putstr_fd("Initiation successful\n", 1);
	param->window = mlx_new_window(param->mlx, WIN_LENGTH, WIN_HEIGHT, filepath);
	if (param->window != NULL)
	{
		ft_putstr_fd("Window successfuly generated\n", 1);
		mlx_key_hook(param->window, key_hook, param);
		mlx_loop(param->mlx);
	}
	else
	{
		ft_putstr_fd("Window error\n", 1);
		param->valid = 0;
	}
	return (param);
}

int	main(int argc, char **argv)
{
	t_param	*param;
	t_map	*map;
	int	error;

	if (argc != 2)
		return (error_in_arguments(argc));
	map = get_map_content(argv[1]);
	if (!map || map->lines_size == -1)
		return (error_while_parsing(map));

	/*
	** Test purpose only
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
	free (map->lines_content);
	free(map);
	error = param->valid;
	free(param);
	if (error)
		return (1);
	return (0);
}
