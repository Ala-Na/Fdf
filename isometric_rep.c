/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_rep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 22:36:32 by anadege           #+#    #+#             */
/*   Updated: 2021/07/02 17:52:10 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "fdf.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265359

/*
** Function to convert any 3D x/y/z coordinates into 2D coordinates i/j with an
** isometric representation according to an alpha angle along the x axis. Alpha is set to 30 
** degree as default but can be modified to have a rotation effect.
*/
void	twoD_iso_coordinates(int x, int y, int z)
{
	double	i;
	double	j;
	double alpha = 30;
	double	val = PI / 180;

	printf("cos %f is %f radian\n", alpha, alpha * val);
	i = x * cos(alpha * val) + y * cos((alpha + 120) * val) + z * cos((alpha - 120) * val);
	j = x * sin(alpha * val) + y * sin((alpha + 120) * val) + z * sin((alpha - 120) * val);
	printf("x %i y %i z %i become i %f j %f\n", x, y, z, i, j);
	//go to draw ? but before pix_per_seg to calculate ? and problem with need of multipe coordinate to draw seg
}

void	recup_threeD_coordinates(t_param *param)
{
	int	x;
	int	y;
	int	z = 0;

	// Vertical
	x = 0;
	while (x < param->map_infos->lines_size)
	{
		y = 0;
		while (y < param->map_infos->nbr_total_lines)
		{
			z = param->map_infos->lines_content[x + y * param->map_infos->lines_size];
			// get iso coordinate and draw segment ?
			y += 1;
		}
		x += 1;
	}

	//Horizontal
	y = 0;
	while (y < param->map_infos->nbr_total_lines)
	{
		x = 0;
		while (x < param->map_infos->lines_size)
		{
			z = param->map_infos->lines_content[x + y * param->map_infos->lines_size];
			// get iso coordinate and draw segment ?
			x += 1;
		}
		y += 1;
	}
}

int main(int argc, char **argv)
{
	if (argc != 4)
		return (1);
	int x = atoi(argv[1]);
	int y = atoi(argv[2]);
	int z = atoi(argv[3]);
	twoD_iso_coordinates(x, y, z);
	return (0);
}
