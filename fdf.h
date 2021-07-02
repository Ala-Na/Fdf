/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:29:19 by anadege           #+#    #+#             */
/*   Updated: 2021/07/02 17:40:05 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
** For test purposes
*/
# include <stdio.h>

# include "./libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <mlx.h>

# define WIN_LENGTH 1000
# define WIN_HEIGHT 800

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
	int		valid;
	void	*mlx;
	void	*window;
	int		win_length;
	int		win_height;
	int		i_center; // = win_length / 2;
	int		j_center; // = win_height / 2;
	int		i_max;
	int		j_max;
	int		alpha;
	int		pix_per_seg;
	t_map	*map_infos;
}	t_param;

/*
** Errors messages functions
*/
int	error_in_arguments(int argc);
int	error_while_parsing(t_map *map);

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
