/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:25:24 by rturker           #+#    #+#             */
/*   Updated: 2022/10/10 09:31:09 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	unsigned char	*d1;
	unsigned char	*d2;

	if (!src)
		return (dst);
	d1 = (unsigned char *)dst;
	d2 = (unsigned char *)src;
	i = 0;
	while (d1[i] && i < n)
	{
		d1[i] = d2[i];
		i++;
	}
	return (dst);
}

/*
#include <stdio.h>
#include <string.h>
int main(){
    unsigned char str[] = "merhaba";
    unsigned char str2[] = "merhaba";
    memcpy(str,str2+2,5);
    ft_memcpy(str2,str2+2,5);
    printf("str1   :%s\nstr2   :%s\n",str,str2);
    printf("str1   :%s\nstr2   :%s\n",str,str2);
}
*/
