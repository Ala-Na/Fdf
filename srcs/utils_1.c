/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 15:42:53 by anadege           #+#    #+#             */
/*   Updated: 2021/07/10 15:43:40 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	return_value(long int res, long int sign)
{
	if (res < 0 && sign > 0)
		return (-1);
	else if (res < 0 && sign < 0)
		return (0);
	res *= sign;
	return ((int)res);
}

int	ft_atoi(const char *nptr)
{
	unsigned int	nbr;
	long int		res;
	long int		sign;

	nbr = 0;
	res = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = *nptr - '0';
		res = res * 10 + nbr;
		nptr++;
	}
	return ((int)return_value(res, sign));
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		i++;
	write(fd, s, i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}
