/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:03:22 by hubretec          #+#    #+#             */
/*   Updated: 2021/11/29 21:07:33 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int	mem_empty(char *memory)
{
	while (*memory)
		if (*(memory++) != -1)
			return (0);
	return (1);
}

char	*fill_line(char *memory)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	line = malloc(sizeof(char) * (ft_strlen(memory, '\n') + 2));
	if (!line)
		return (NULL);
	while (memory[j] < 0)
		j++;
	while (memory[j] != '\n' && memory[j])
	{
		line[i++] = memory[j];
		memory[j++] = -1;
	}
	if (memory[j] == '\n')
	{
		line[i++] = '\n';
		memory[j++] = -1;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*memory;

	memory = get_memory(memory, fd);
	if (!memory)
		return (NULL);
	line = fill_line(memory);
	if (memory && mem_empty(memory))
	{
		free(memory);
		memory = 0;
	}
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
	if (!line)
		return (0);
	printf("%s", line);
	free(line);
	return (0);
}
