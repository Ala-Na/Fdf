/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:06:19 by anadege           #+#    #+#             */
/*   Updated: 2021/06/28 23:35:48 by anadege          ###   ########.fr       */
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
			while (ft_isdigit(*line))
				line++;
			line++;
		}
	}
	return (int_line);
}

int	verify_line_format_and_size(char **line)
{
	int	line_size;

	line_size = 0;
	while (**line != '\n' && **line != '\0')
	{
		if (!ft_isdigit(**line))
			return (-1);
		while (ft_isdigit(**line))
			(*line)++;
		while (**line == ' ')
			(*line)++;
		if (!ft_isdigit(**line) && **line != '\n' && **line != '\0')
			return (-1);
		line_size++;
	}
	(*line)++;
	return (line_size);
}

t_map	transform_map_content(char *content)
{
	t_map	map;
	int		curr_line_size;
	int		index;

	map.nbr_total_lines = 0;
	map.lines_size = verify_line_format_and_size(&content);
	printf("content : %s\n", content);
	printf("%i\n", map.lines_size);
	curr_line_size = verify_line_format_and_size(&content);
	map.nbr_total_lines += 1;
	while (curr_line_size != -1 && *content != '\0')
	{
		printf("content : %s\n", content);
		if (curr_line_size != map.lines_size)
			map.lines_size = -1;
		map.nbr_total_lines += 1;
		curr_line_size = verify_line_format_and_size(&content);
	}
	if (curr_line_size == -1 && *content != '\0')
		map.lines_size = -1;
	map.lines_content = convert_lines_to_int(content, map.lines_size, map.nbr_total_lines);
	if (!map.lines_content)
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
		ft_putstr_fd("Bad filepath/filename\n", 1);
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
	map = transform_map_content(content);
	free(content);
	if (map.lines_size == -1)
		return (-1);
	/* Test to delete */
	int i = 0;
	while (i < (map.lines_size * map.nbr_total_lines))
		printf("%i ", map.lines_content[i++]);
	printf("\n");
	free(map.lines_content);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error in arguments\n", 1);
		return (1);
	}
	if(get_map_content(argv[1]) != 0)
	{
		ft_putstr_fd("Error parsing map\n", 1);
		return(1);
	}
	return(0);
}
