/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:03:22 by hubretec          #+#    #+#             */
/*   Updated: 2021/11/28 15:21:33 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char	*ft_realloc(char buff[2], char *content)
{
	int		i;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(content) + 2));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (content[i])
	{
		str[i] = content[i];
		i++;
	}
	str[i++] = buff[0];
	str[i] = '\0';
	if (*content)
		free(content);
	return (str);
}

char	*get_next_line(int fd)
{
	char		buff[2];
	static char	*line;

	line = "";
	while (read(fd, buff, 1) > 0 && *buff != '\n')
		line = ft_realloc(buff, line);
	return (line);
}

#include <stdio.h>
int main(int ac, char **av)
{
	int fd;
	char *line;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	return (0);
}
