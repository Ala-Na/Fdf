/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:06:19 by anadege           #+#    #+#             */
/*   Updated: 2021/06/29 21:15:42 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "./libft/libft.h"

typedef struct s_map
{
	int	lines_size;
	int	nbr_total_lines;
	int	*lines_content;
}	t_map;

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

void	transform_map_content(char *content, t_map	*map)
{
	(*map).lines_content = convert_lines_to_int(content, (*map).lines_size,
			(*map).nbr_total_lines);
	if ((*map).lines_content == NULL)
		(*map).lines_size = -1;
	return ;
}

t_map	prepare_map_content(char *content)
{
	t_map	map;
	int		curr_line_size;
	int		line_index;

	line_index = 0;
	map.nbr_total_lines = 0;
	map.lines_size = verify_line_format_and_size(content, &line_index);
	curr_line_size = map.lines_size;
	map.nbr_total_lines += 1;
	while (curr_line_size != -1 && content[line_index] != '\0')
	{
		if (curr_line_size != map.lines_size)
			map.lines_size = -1;
		map.nbr_total_lines += 1;
		curr_line_size = verify_line_format_and_size(content, &line_index);
	}
	if (curr_line_size == -1 && content[line_index] != '\0')
		map.lines_size = -1;
	return (map);
}

int	close_map(int size_read, int fd_map)
{
	if (size_read < 0)
	{
		ft_putstr_fd("Error while reading map\n", 1);
		return (-1);
	}
	close(fd_map);
	return (0);
}

int	read_map_content(int fd_map, char **content)
{
	char	buffer[10001];
	int		size_read;
	char	*tmp_content;
	int		max_read;

	max_read = 0;
	size_read = read(fd_map, buffer, 10000);
	while (size_read > 0)
	{
		tmp_content = *content;
		buffer[size_read] = '\0';
		max_read += size_read;
		if (max_read <= 10000)
			*content = ft_strdup(buffer);
		else
		{
			*content = ft_strjoin(tmp_content, buffer);
			free(tmp_content);
		}
		if (!(*content))
			return (-1);
		size_read = read(fd_map, buffer, 10000);
	}
	return (close_map(size_read, fd_map));
}

int	open_map(char *filepath_map)
{
	int	fd_map;

	fd_map = open(filepath_map, O_RDONLY);
	if (fd_map == -1)
		ft_putstr_fd("Bad filepath or filename\n", 1);
	return (fd_map);
}

int	get_map_content(char *filepath_map)
{
	int		fd_map;
	char	*content;
	t_map	map;

	content = NULL;
	fd_map = open_map(filepath_map);
	if (fd_map == -1 || read_map_content(fd_map, &content) == -1)
		return (-1);
	map = prepare_map_content(content);
	if (map.lines_size != -1)
		transform_map_content(content, &map);
	free(content);
	if (map.lines_size == -1)
		return (-1);
	//go to function to interpret
	int i = 1;
	while (i <= (map.lines_size * map.nbr_total_lines))
	{
		printf("%4i", map.lines_content[i - 1]);
		if (i % map.lines_size == 0)
			printf("\n");
		i++;
	}
	printf("\n");
	free(map.lines_content);
	return (0);
}

/* NE PAS OUBLIER DE FREE map.lines_content */

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error in arguments\n", 1);
		return (1);
	}
	if (get_map_content(argv[1]) != 0)
	{
		ft_putstr_fd("Error while parsing map\n", 1);
		return (1);
	}
	return (0);
}
