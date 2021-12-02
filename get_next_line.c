/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:03:22 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/02 09:49:02 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int	mem_empty(char *memory)
{
	while (*memory)
		if (*(memory++) != 127)
			return (0);
	return (1);
}

#include <stdio.h>

char	*get_memory(int fd)
{
	int		bytes;
	char	*tmp;
	char	*memory;

	memory = 0;
	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	bytes = 1;
	while ((!memory || !ft_strchr(tmp, '\n')) && bytes)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(tmp);
			free(memory);
			return (NULL);
		}
		tmp[bytes] = '\0';
		memory = ft_strjoin(memory, tmp);
	}
	free(tmp);
	if (!bytes && !*memory)
		return (NULL);
	return (memory);
}

char	*fill_line(char *memory)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (memory[i] == 127)
		i++;
	line = malloc(sizeof(char) * (line_len(memory, i) + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (memory[i] && memory[i] != '\n')
	{
		line[j++] = memory[i];
		memory[i++] = 127;
	}
	if (memory[i] == '\n')
	{
		line[j++] = '\n';
		memory[i++] = 127;
	}
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*memory;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!memory)
	{
		memory = get_memory(fd);
		if (!memory)
			return (NULL);
	}
	line = fill_line(memory);
	if (mem_empty(memory))
	{
		free(memory);
		memory = 0;
	}
	return (line);
}

#include <fcntl.h>

int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
