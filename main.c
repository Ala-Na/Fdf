/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 20:14:02 by elanna            #+#    #+#             */
/*   Updated: 2021/06/30 14:58:19 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_param *param)
{
	printf("%i\n", keycode);
	if (keycode == 65307)
	{
		mlx_destroy_window(param->mlx, param->window);
		exit(0);
		return (1);
	}
	return (0);
}

int	init_fdf(char *filepath_map)
{
	
}

int	main(int argc, char **argv)
{
	t_param	param;
	t_map	map;

	if (argc != 2)
	{
		ft_putstr_fd("Error in arguments\n", 1);
		return (1);
	}
	map = get_map_content(argv[1]);
	if (map.lines_size == -1)
	{
		ft_putstr_fd("Error while parsing map\n", 1);
		return (1);
	}

	/*
	** Test purpose only
	*/
	int i = 1;
	while (i <= (map.lines_size * map.nbr_total_lines))
	{
		printf("%4i", map.lines_content[i - 1]);
		if (i % map.lines_size == 0)
			printf("\n");
		i++;
	}
	printf("\n");
	/*
	** End test purpose
	*/

	param.mlx = mlx_init();
	if (param.mlx == NULL)
	{
		printf("Init error\n");
		return (1);
	}
	printf("Init successful\n");
	param.window = mlx_new_window(param.mlx, WIN_LENGTH, WIN_HEIGHT, argv[1]);
	if (param.window != NULL)
	{
		printf("Window successful\n");
		key = mlx_key_hook(param.window, key_hook, &param);
		mlx_loop(mlx.mlx);
	}
	else
	{
		printf("Window error\n");
		return (1);
	}
	free (map.lines_content);
	return (0);
}
