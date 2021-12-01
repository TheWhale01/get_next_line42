/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:02:53 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/01 11:17:07 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stddef.h>

int		ft_strlen(char *str, char c);

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);

void	*ft_calloc(size_t nmemb, size_t size);

#endif