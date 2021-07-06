/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:29:19 by anadege           #+#    #+#             */
/*   Updated: 2021/07/06 15:18:47 by anadege          ###   ########.fr       */
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

# define WIN_LENGTH 1000
# define WIN_HEIGHT 800
# define ALPHA 30
# define PI 3.14159265359
# define WHITE 0xFFFFFFFF

/*
** Structure to stock x / y coordinates
*/ 
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	i;
	int	j;
}	t_point ;

/*
** Structure for stocking map content
*/
typedef struct s_map
{
	int	lines_size;
	int	nbr_total_lines;
	int	*lines_content;
	int	max_z;
	int	min_z;
}	t_map;

/*
** Structure for stocking all parameters
*/
typedef struct s_param
{
	int		valid;
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
	t_map	*map_infos;
}	t_param;


void	two_dim_iso_coordinates(t_param *param, t_point *point);
void	recup_three_dim_z(t_param *param, t_point *point);
int	prep_horizontals_line(t_param *param, t_point *prev_point, t_point *curr_point);
int	prep_verticals_line(t_param *param, t_point *prev_point, t_point *curr_point);
void	init_point(t_point *point);
int	init_recup_three_dim_coordinates(t_param *param);

int	brasenham_segment(t_param *param, t_point *start_point, t_point *end_point);
/*
** Errors messages functions
*/
int	error_in_arguments(int argc);
int	error_while_parsing(t_map *map);

void	print_point(t_point *point);

int	seek_potential_max_i(t_param *param);
int	seek_potential_max_j(t_param *param);
void	adjust_pixel_per_segment(t_param *param);
int	seek_max_z(t_map *map);
int	seek_min_z(t_map *map);

int	put_pixel_default_color(t_param *param, int i, int j);
int	manage_image(t_param *param);
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

#endif
