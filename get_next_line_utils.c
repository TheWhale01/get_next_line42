/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:52:58 by hubretec          #+#    #+#             */
/*   Updated: 2021/11/29 21:03:51 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(str, 0) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (str[++i])
		new[i] = str[i];
	new[i] = '\0';
	free(str);
	return (new);
}

char	*get_memory(char *memory, int fd)
{
	int		bytes;
	char	*buff;

	if (!memory || !*memory)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
			return (NULL);
		else if (!bytes)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		memory = ft_strdup(buff);
	}
	return (memory);
}
