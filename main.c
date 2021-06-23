/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 20:14:02 by elanna            #+#    #+#             */
/*   Updated: 2021/06/23 20:19:42 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

int	main()
{
	void *mlx;

	mlx = mlx_init();
	if (mlx == NULL)
	{
		printf("Error\n");
		return (1);
	}
	printf("Init successful\n");
	return (0);
}
