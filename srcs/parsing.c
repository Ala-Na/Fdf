/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:06:19 by anadege           #+#    #+#             */
/*   Updated: 2021/07/10 15:39:44 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	*convert_lines_to_int(char *line, int lines_size, int nbr_total_lines)
{
	int		*int_line;
	int		int_nbr;

	int_nbr = 0;
	int_line = malloc(sizeof(*int_line) * (lines_size * nbr_total_lines));
	if (!int_line)
		return (NULL);
	while (int_nbr < (lines_size * nbr_total_lines))
	{
		int_line[int_nbr] = ft_atoi(line);
		int_nbr++;
		if (int_nbr < (lines_size * nbr_total_lines))
		{
			if (*line == '-')
				line++;
			while (ft_isdigit(*line))
				line++;
			while (*line == ' ' || *line == '\n')
				line++;
		}
	}
	return (int_line);
}

int	verify_line_format_and_size(char *line, int *line_index)
{
	int	line_size;

	line_size = 0;
	while (line[*line_index] != '\n' && line[*line_index] != '\0')
	{
		while (line[*line_index] == ' ')
			(*line_index)++;
		if (!ft_isdigit(line[*line_index]) && line[*line_index] != '-')
			return (-1);
		if (line[*line_index] == '-')
			(*line_index)++;
		while (ft_isdigit(line[*line_index]))
			(*line_index)++;
		while (line[*line_index] == ' ')
			(*line_index)++;
		if (!ft_isdigit(line[*line_index]) && line[*line_index] != '-'
			&& line[*line_index] != '\n' && line[*line_index] != '\0')
			return (-1);
		line_size++;
	}
	if (line[*line_index] != '\0')
		(*line_index)++;
	return (line_size);
}

void	transform_map_content(char *content, t_map	**map)
{
	(*map)->lines_content = convert_lines_to_int(content, (*map)->lines_size,
			(*map)->nbr_total_lines);
	if ((*map)->lines_content == NULL)
		(*map)->lines_size = -1;
	return ;
}

t_map	*prepare_map_content(char *content)
{
	t_map	*map;
	int		curr_line_size;
	int		line_index;

	map = malloc(sizeof(*map));
	if (!map)
		return (NULL);
	line_index = 0;
	map->nbr_total_lines = 0;
	map->lines_size = verify_line_format_and_size(content, &line_index);
	curr_line_size = map->lines_size;
	map->nbr_total_lines += 1;
	while (curr_line_size != -1 && content[line_index] != '\0')
	{
		if (curr_line_size != map->lines_size)
		{
			map->lines_size = -1;
		}
		map->nbr_total_lines += 1;
		curr_line_size = verify_line_format_and_size(content, &line_index);
	}
	if (curr_line_size == -1 && content[line_index] != '\0')
		map->lines_size = -1;
	return (map);
}

t_map	*get_map_content(char *filepath_map)
{
	int		fd_map;
	char	*content;
	t_map	*map;

	content = NULL;
	fd_map = open_map(filepath_map);
	if (fd_map == -1 || read_map_content(fd_map, &content) == -1)
		return (NULL);
	map = prepare_map_content(content);
	if (map && map->lines_size != -1)
		transform_map_content(content, &map);
	free(content);
	return (map);
}
