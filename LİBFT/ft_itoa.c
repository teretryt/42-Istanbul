/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:20:10 by rturker           #+#    #+#             */
/*   Updated: 2022/10/09 19:21:31 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	digits(long n)
{
	long	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return	(i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		l;
	long	tmp;

	tmp = n;
	l = digits(tmp);

	str = (char*)malloc(l + 1);
    if (!str)
        return (NULL);
	str[l] = '\0';
	if (tmp < 0)
	{
		str[0] = '-';
		tmp *= -1;
	}
	if (tmp == 0)
	{
		str[0] = 48;
		return	(str);
	}
	while (tmp > 0)
	{
		str[l - 1] = (tmp	% 10) + 48;
		tmp /= 10;
		l--;
	}
	return	(str);
}

/*
#include <stdio.h>
int	main()
{
	char d[] = "-243";
	printf("%s",ft_itoa(-243)[3]);
}
*/
