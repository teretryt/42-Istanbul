/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:29:30 by rturker           #+#    #+#             */
/*   Updated: 2022/10/06 17:23:12 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;
	int		t;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	t = i + j; 
	new = (char*)malloc(t + 1);
	if (!new)
		return NULL;
	i = 0;
	while (s1[i]){
		new[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = '\0';
	return new;
}

/*
int main()
{
	printf("%s",ft_strjoin("mer","haba"));
}
*/
