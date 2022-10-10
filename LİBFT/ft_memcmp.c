/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:50:53 by rturker           #+#    #+#             */
/*   Updated: 2022/10/09 20:07:34 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	if (n == 0)
		return (0);	
	unsigned char *s1t = (unsigned char *)s1;
	unsigned char *s2t = (unsigned char *)s2;

	i = 0;
	while((s1t[i] || s2t[i]) && (i < n))
	{
		if (s1t[i] != s2t[i])
			return (s1t[i] - s2t[i]);
		i++;
	}
	return (0);
}
/*
int main()
{
	char d[] = "asda";
	char f[] = "";
	printf("%d",memcmp(d,f,3));
}*/
