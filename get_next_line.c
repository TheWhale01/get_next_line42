/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:03:22 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/01 17:28:26 by hubretec         ###   ########.fr       */
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

int	line_complete(char *memory)
{
	while (*memory)
		if (*(memory++) == '\n')
			return (1);
	return (0);
}

char	*get_memory(int fd)
{
	int		bytes;
	char	*tmp;
	char	*memory;

	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	memory = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp || !memory)
		return (NULL);
	while (!line_complete(memory))
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes <= 0 || (!bytes && !*tmp))
		{
			free(tmp);
			free(memory);
			return (NULL);
		}
		tmp[bytes] = '\0';
		memory = ft_strjoin(memory, tmp);
	}
	free(tmp);
	return (memory);
}

char	*fill_line(char *memory)
{
	int		i;
	int		j;
	char	*line;

	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	while (memory[j] == 127)
		j++;
	while (memory[j] != '\n' && memory[j])
	{
		line[i++] = memory[j];
		memory[j++] = 127;
	}
	if (memory[j] == '\n')
	{
		line[i++] = memory[j];
		memory[j++] = 127;
	}
	line[i] = '\0';
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


//*memory && bytes > 0