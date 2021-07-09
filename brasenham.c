/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brasenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:48:24 by anadege           #+#    #+#             */
/*   Updated: 2021/07/09 15:55:57 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_point(t_point *point, t_param *param)
{
	int max;
	int i;

	i = 0;
	max = param->map_infos->nbr_total_lines * param->map_infos->lines_size;
	while (i < max)
	 {
		printf("point i is %i, point j is %i\n", point->i[i], point->j[i]);
		i++;
	 }
}
