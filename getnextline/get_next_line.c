/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:55:04 by rturker           #+#    #+#             */
/*   Updated: 2022/10/26 12:56:54 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*scan(int fd, char *s)
{
	int		i;
	char	*l;
	int		lw;

	i = 0;
	l = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!l)
		return (NULL);
	lw = 1;
	while (lw != 0 && !ft_strchr(s, '\n'))
	{
		lw = read(fd, l, BUFFER_SIZE);
		if (lw == -1)
		{
			free(l);
			return (NULL);
		}
		l[lw] = 0;
		s = add(s, l);
		if (!s)
			return (NULL);
	}
	free(l);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*stc;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stc = scan(fd, stc);
	if (!stc)
		return (NULL);
	str = line(stc);
	stc = next(stc);
	return (str);
}
