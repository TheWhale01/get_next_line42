/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:03:22 by hubretec          #+#    #+#             */
/*   Updated: 2021/11/28 22:15:21 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

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

char	*ft_realloc(char c, char *content)
{
	int		i;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(content) + 2));
	if (!str)
		return (0);
	i = 0;
	if (content)
	{
		while (content[i])
		{
			str[i] = content[i];
			i++;
		}
	}
	str[i++] = c;
	str[i] = '\0';
	if (content)
		if (*content)
			free(content);
	return (str);
}

#include <stdio.h>
char	*get_next_line(int fd)
{
	int			byte;
	char		c;
	static char	*line;

	line = 0;
	while (1 && byte > 0)
	{
		byte = read(fd, &c, 1);
		if (byte > 0 && c != '\n')
			line = ft_realloc(c, line);
		if (c == '\n' || !byte)
		{
			if (byte)
				line = ft_realloc(c, line);
			return (line);
		}
	}
	return (NULL);
}

int main(int ac, char **av)
{
	int fd;
	char *line;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
