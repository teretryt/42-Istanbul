/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 21:44:29 by rturker           #+#    #+#             */
/*   Updated: 2022/11/01 22:49:24 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	accept(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("Message received by 'Server' \n");
}

int	ft_atoi(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	return (num);
}

void	send_string(int pid, char *str)
{
	int				i;
	unsigned char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if ((c >> i) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
		}
	}
}

int	main(int ac, char **argv)
{
	int	byt;
	int	pid;
	int	x;

	if (ac == 3)
	{
		pid = ft_atoi(argv[1]);
		signal(SIGUSR1, accept);
		send_string(pid, argv[2]);
		x = 0;
	}
	else
	{
		ft_printf("Hatalı Giriş\n");
		x = 1;
	}
	if (x != 1)
	{
		byt = 8;
		while (byt--)
		{
			kill(pid, SIGUSR2);
			usleep(50);
		}
	}
}
