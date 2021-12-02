/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:03:22 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/02 10:57:35 by hubretec         ###   ########.fr       */
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

char	*get_memory(int fd, int *bytes)
{
	char	*tmp;
	char	*memory;

	memory = 0;
	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	while ((!memory || !ft_strchr(tmp, '\n')) && *bytes)
	{
		*bytes = read(fd, tmp, BUFFER_SIZE);
		if (*bytes < 0)
		{
			free(tmp);
			if (memory)
				free(memory);
			return (NULL);
		}
		tmp[*bytes] = '\0';
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
	int			bytes;
	char		*line;
	static char	*memory;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	bytes = 1;
	if (!memory)
	{
		memory = get_memory(fd, &bytes);
		if (!memory)
			return (NULL);
		else if (!bytes && !*memory)
		{
			free(memory);
			return (NULL);
		}
	}
	line = fill_line(memory);
	if (mem_empty(memory))
	{
		free(memory);
		memory = 0;
	}
	return (line);
}
