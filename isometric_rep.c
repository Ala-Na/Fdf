/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_rep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 22:36:32 by anadege           #+#    #+#             */
/*   Updated: 2021/06/29 22:10:37 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h> 

typedef struct s_cart_pnt
{
	int		x;
	int		y;
	int		z;
	void	*next_point;
} t_cart_pnt;

typedef struct s_iso_pnt
{
	int		x;
	int		y;
	void	*next_point;
} t_iso_pnt;

typedef struct	s_win_param
{
	int	width;
	int	height;
} t_win_param;

t_iso_pnt	point_to_isometric(t_cart_pnt cartesian, s_win_param window)
{
t_iso_pnt	isometric;


}
