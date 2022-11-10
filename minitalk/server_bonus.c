/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 21:53:51 by rturker           #+#    #+#             */
/*   Updated: 2022/11/01 22:01:14 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	handler(int sig, siginfo_t *info, void *cnt)
{
	int			x;
	static int	bit = 7;
	static int	set = 0;

	(void)cnt;
	x = 0;
	if (sig == SIGUSR1)
		x = 1;
	else if (sig == SIGUSR2)
		x = 0;
	set += x << bit;
	if (bit == 0)
	{
		if (set == 0)
			kill(info->si_pid, SIGUSR1);
		ft_printf("%c", set);
		bit = 7;
		set = 0;
	}
	else
		bit--;
}

int	main(int argc, char **argv)
{
	struct sigaction	sig;
	int					pid;

	pid = getpid();
	ft_printf("PİD: %d\n", pid);
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = handler;
	sigaction(SIGUSR1, &sig, 0);
	sigaction(SIGUSR2, &sig, 0);
	while (1)
		pause();
}
