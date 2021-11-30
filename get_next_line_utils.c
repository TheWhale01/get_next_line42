/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:52:58 by hubretec          #+#    #+#             */
/*   Updated: 2021/11/30 14:57:25 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(const char *str, char c)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		s1len;
	char	*str;

	s1len = ft_strlen(s1, 0);
	str = (char *)malloc(sizeof(char) * (s1len + ft_strlen(s2, 0) + 1));
	if (!str)
		return (0);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[i - s1len])
	{
		str[i] = s2[i - s1len];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_memory(int fd)
{
	int		bytes;
	char	*memory;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	memory = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!memory)
		return (NULL);
	bytes = read(fd, memory, BUFFER_SIZE);
	if (bytes < 0)
		return (NULL);
	else if (!bytes)
	{
		free(memory);
		return (NULL);
	}
	memory[bytes] = '\0';
	return (memory);
}
