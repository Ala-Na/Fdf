/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:29:19 by anadege           #+#    #+#             */
/*   Updated: 2021/07/10 00:15:41 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h> // Pour les tests uniquements !

# include "./libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <mlx.h>

# define WIN_LENGTH 1900
# define WIN_HEIGHT 1000
# define ALPHA 30
# define PI 3.14159265359
# define BLUE 0xFF

/*
** Structure used to draw segments. Variables are 
** needed for the brasenham algorithm (see Wikipedia).
*/
typedef struct s_brasenham
{
	int	i_start;
	int	i_end;
	int	j_start;
	int	j_end;
	int	delta_i;
	int	delta_j;
	int	sign_i;
	int	sign_j;
	int	error;
	int	mult_error;
}	t_brasenham;

/*
** Structure to stock x / y / z coordinates and convert
** them as i / j coordinates (3D to 2D).
*/ 
typedef struct s_point
{
	int	position;
	int	x;
	int	y;
	int	z;
	int	*i;
	int	*j;
}	t_point;

/*
** Structure for stocking map content
*/
typedef struct s_map
{
	int	lines_size;
	int	nbr_total_lines;
	int	*lines_content;
}	t_map;

/*
** Structure for stocking all parameters
*/
typedef struct s_param
{
	int		perspective;
	void	*mlx;
	void	*window;
	void	*img;
	char	*img_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		win_length; //WIN_LENGTH
	int		win_height; // WIN_HEIGHT
	int		img_length; // win_length - cste pour éviter bords
	int		img_height; // m chose
	int		i_start;
	int		j_start; 
	int		alpha;
	int		pix_per_seg;
	int		default_color;
	int		depth;
	t_map	*map_infos;
	t_point	*points;
}	t_param;

void	modify_depth(t_param *param, int modif);
void	erase_modifications(t_param *param);
void	modify_perspective(t_param *param);
void	modify_position(t_param *param, int modif);

/*
** Functions to adjust display inside windows limits at launch.
*/
void	apply_adjustments(t_param *param);
int	adjust_start(t_param *param, int *values);
int	seek_maximum_value(t_param *param, int *values);
int	adjust_pixel_per_segment(t_param *param);

/*
** Functions to transform 3D coordinates in 2D coordinates.
*/
void	two_dim_iso_coordinates(t_point *point, t_param *param);
void	two_dim_plane_coordinates(t_point *point, t_param *param);
void	fill_array_of_points(t_point *point, t_param *param);
int	init_point(t_point *point, t_param *param);
t_point	*recup_coordinates(t_param *param);

/*
** Functions to draw segments between coordinates.
*/
int get_delta_and_sign(int start_value, int end_value, int *sign);
void	brasenham_segment(t_param *param, int start, int end);
void	draw_grid(t_param *param);

/*
** Errors messages functions
*/
int	error_in_arguments(int argc);
int	error_while_parsing(t_map *map);
void	*init_error(char *str, t_param *param);

/*
** Test purpose only
*/
void	print_point(t_point *point, t_param *param);

/*
** Draw pixel and image managments functions.
*/
void	put_pixel_default_color(t_param *param, int i, int j);
void	re_manage_image(t_param *param);
void	manage_image(t_param *param);
/*
** Parsing functions
*/
int	*convert_lines_to_int(char *line, int lines_size, int nbr_total_lines);
int	verify_line_format_and_size(char *line, int *line_index);
void	transform_map_content(char *content, t_map **map);
t_map	*prepare_map_content(char *content);
int	close_map(int size_read, int fd_map);
int	read_map_content(int fd_map, char **content);
int	open_map(char *filepath_map);
t_map	*get_map_content(char *filepath_map);

/*
** Functions for clean exit
*/
void	free_points(t_point *points);
void	clean_exit(t_param *param);

/*
** Functions for evenments
*/
int	key_hook(int keycode, t_param *param);
int	mouse_hook(int mousecode, int x, int y, t_param *param);

/*
** Main and initialization functions
*/
t_param	*init_param(t_map *map);
t_param	*fdf(t_map *map, char *filepath);

#endif
