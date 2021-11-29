/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:03:22 by hubretec          #+#    #+#             */
/*   Updated: 2021/11/28 23:01:56 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*addchar(char c, char *str)
{
	int		i;
	char	*new;

	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		return (0);
	if (!str)
	{
		new[0] = c;
		new[1] = '\0';
		return (new);
	}
	i = -1;
	while (str[++i])
		new[i] = str[i];
	new[i++] = c;
	new[i] = '\0';
	if (*str)
		free(str);
	return (new);
}

char	*get_next_line(int fd)
{
	int			byte;
	char		c;
	static char	*line;

	c = 0;
	line = 0;
	byte = 1;
	if (fd < 0)
		return (NULL);
	while (byte > 0)
	{
		byte = read(fd, &c, 1);
		while (byte > 0 && c != '\n')
		{
			line = addchar(c, line);
			byte = read(fd, &c, 1);
		}
		if (c == '\n' || !byte)
		{
			if (byte)
				line = addchar(c, line);
			return (line);
		}
	}
	return (NULL);
}
