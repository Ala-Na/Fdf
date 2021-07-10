/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 15:43:56 by anadege           #+#    #+#             */
/*   Updated: 2021/07/10 15:52:10 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_strdup(const char *s)
{
	int		size;
	char	*dest;
	int		i;

	i = 0;
	size = 0;
	while (s[size])
		size++;
	dest = malloc(sizeof(*dest) * (size + 1));
	if (!dest)
		return (0);
	while (s[i] != 0)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	size;
	char	*str;

	i = -1;
	size = 0;
	if (!s1 && !s2)
		return (NULL);
	while (s1 && s1[size])
		size++;
	while (s2 && s2[++i])
		size++;
	str = malloc(sizeof(*str) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		str[i++] = *s1++;
	while (s2 && *s2)
		str[i++] = *s2++;
	str[size] = 0;
	return (str);
}

void	ft_putnbr_fd(int n, int fd)
{
	char			c;
	unsigned int	nb;

	if (n < 0)
	{
		c = '-';
		write(fd, &c, 1);
		nb = -n;
	}
	else
		nb = n;
	if (nb / 10 > 0)
		ft_putnbr_fd(nb / 10, fd);
	c = '0' + (nb % 10);
	write(fd, &c, 1);
}
