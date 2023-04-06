/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:17:28 by rturker           #+#    #+#             */
/*   Updated: 2022/11/20 12:17:30 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_rgb2hex(t_rgb rgb)
{
	return (((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (s == 0)
		return ;
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}

void	init_rgb(t_fractal *f)
{
	f->rgb.r = 5;
	f->rgb.g = 5;
	f->rgb.b = 5;
	f->rgbarr[0] = 4;
	f->rgbarr[1] = 4;
	f->rgbarr[2] = 12;
	f->rgbarr[3] = 3;
	f->rgbarr[4] = 15;
	f->rgbarr[5] = 4;
	f->rgbarr[6] = 5;
	f->rgbarr[7] = 24;
	f->rgbarr[8] = 0;
}

void	change_julia(t_fractal *f)
{
	static int	i = 0;

	i++;
	if (i == 4)
		i = 0;
	f->j.real = f->juliar[i];
	f->j.imag = f->juliai[i];
}

void	init_juliari(t_fractal *f)
{
	f->juliar[0] = 0.285;
	f->juliai[0] = 0.01;
	f->juliar[1] = -0.7269;
	f->juliai[1] = 0.1889;
	f->juliar[2] = -0.70176 ;
	f->juliai[2] = -0.3842;
	f->juliar[3] = -0.8;
	f->juliai[3] = 0.156;
}
