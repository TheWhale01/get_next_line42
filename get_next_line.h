/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:02:53 by hubretec          #+#    #+#             */
/*   Updated: 2021/11/30 14:56:36 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

int		ft_strlen(char *str, char c);

char	*get_memory(int fd);
char	*ft_strdup(char *str);
char	*get_next_line(int fd);

#endif