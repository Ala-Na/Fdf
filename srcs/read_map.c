/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 15:34:30 by anadege           #+#    #+#             */
/*   Updated: 2021/07/10 15:36:47 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
