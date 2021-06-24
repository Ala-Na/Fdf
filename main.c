/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 20:14:02 by elanna            #+#    #+#             */
/*   Updated: 2021/06/24 16:55:22 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_mlx
{
	void	*mlx;
	void	*window;
}		t_mlx;

int	key_hook(int keycode, t_mlx *param)
{
	printf("%i\n", keycode);
	if (keycode == 65307)
	{
		mlx_destroy_window(param->mlx, param->window);
		return (1);
	}
	return (0);
}

int	main()
{
	t_mlx	mlx;
	int key;

	key = 0;
	mlx.mlx = mlx_init();
	if (mlx.mlx == NULL)
	{
		printf("Init error\n");
		return (1);
	}
	printf("Init successful\n");
	mlx.window = mlx_new_window(mlx.mlx, 1000, 800, "title_to_change");
	if (mlx.window != NULL)
	{
		printf("Window successful\n");
		key = mlx_key_hook(mlx.window, key_hook, &mlx);
		mlx_loop(mlx.mlx);
	}
	else
	{
		printf("Window error\n");
		return (1);
	}
	return (0);
}
