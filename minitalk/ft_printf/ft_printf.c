/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:03:09 by rturker           #+#    #+#             */
/*   Updated: 2022/10/15 15:13:18 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	negorpos(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		if (n == -2147483648)
			return (ft_putnbr_base(2147483648, "0123456789") + 1);
		n = -n;
		return (ft_putnbr_base(n, "0123456789") + 1);
	}
	return (ft_putnbr_base(n, "0123456789"));
}

int	type_control(va_list list, char *c)
{
	int	len;

	len = 0;
	if (c[1] == 's')
		return (ft_putstr(va_arg(list, char *)));
	else if (c[1] == 'd' || c[1] == 'i')
		return (negorpos(va_arg(list, int)));
	else if (c[1] == 'x')
		return (ft_putnbr_base(va_arg(list, unsigned int), "0123456789abcdef"));
	else if (c[1] == 'p')
	{
		ft_putstr("0x");
		return (ft_putnbr_base(va_arg(list, unsigned long),
				"0123456789abcdef") + 2);
	}
	else if (c[1] == 'u')
		return (ft_putnbr_base(va_arg(list, unsigned int), "0123456789"));
	else if (c[1] == 'c')
		return (ft_putchar(va_arg(list, int)));
	else if (c[1] == 'X')
		return (ft_putnbr_base(va_arg(list, unsigned int), "0123456789ABCDEF"));
	else if (c[1] == '%')
		return (ft_putchar('%'));
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	lst;
	int		i;
	int		len;

	va_start(lst, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += type_control(lst, (char *)&str[i]);
			i++;
		}
		else
			len += ft_putchar(str[i]);
		i++;
	}
	return (len);
}
/*
#include <stdio.h>
int main() {
    
    //char**d = multiplejoin(3,"merhaba","naber","nasılsın");
    int a = 565;
    int b = 854;
    char *c;
    char ch = 'R';
    double hg =  25.898;
    printf("%%%%ramazan\n%s");
    //ft_printf("%d",ft_printf("%s",c));
    return 0;
}*/