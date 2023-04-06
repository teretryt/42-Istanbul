/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsets.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:05:10 by rturker           #+#    #+#             */
/*   Updated: 2022/11/20 12:05:37 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_fset(t_fractal *f)
{
	if (f->fractal == JULIA)
	{
		f->zoom = 3;
		f->maxiter = 90;
		f->j.real = f->juliar[0];
		f->j.imag = f->juliai[0];
	}
	else if (f-> fractal == MANDELBROT)
	{
		f->zoom = 2;
		f->maxiter = 80;
	}
}

void	mandelbrot(t_fractal *f, t_cn z, t_cn c, int *i)
{
	double	temp;

	while (++(*i) < f->maxiter && z.real * z.real + z.imag * z.imag < 4)
	{
		temp = z.real;
		z.real = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * temp * z.imag + c.imag;
	}
}

void	julia(t_fractal	*f, t_cn z, int *i)
{
	double	temp;

	while (++(*i) < f->maxiter && z.real * z.real + z.imag * z.imag < 4)
	{
		temp = z.real;
		z.real = z.real * z.real - z.imag * z.imag + f->j.real;
		z.imag = 2 * temp * z.imag + f->j.imag;
	}
}

void	nextpalet(t_fractal *f)
{
	static int	j = 0;

	f->rgb.r = f->rgbarr[j];
	f->rgb.g = f->rgbarr[j + 1];
	f->rgb.b = f->rgbarr[j + 2];
	f->color = ft_rgb2hex(f->rgb);
	j++;
	if (j == 3)
		j = 0;
}
