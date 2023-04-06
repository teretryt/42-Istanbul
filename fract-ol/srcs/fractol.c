/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:10:45 by rturker           #+#    #+#             */
/*   Updated: 2022/11/20 12:10:46 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fractal(t_fractal *f)
{
	f->counter.y = 0;
	while (f->counter.y < HEIGHT)
	{
		f->counter.x = -1;
		while (++f->counter.x < WIDTH)
			draw(f);
		++f->counter.y;
	}
	mlx_put_image_to_window(f->img.mlx, f->img.win, f->img.image, 0, 0);
}

void	draw(t_fractal *f)
{
	t_cn				z;
	t_cn				c;
	int					i;
	unsigned int		in_color;

	c.real = ((f->counter.x * f->zoom) / (WIDTH / 2)) - (f->zoom + f->srate.x);
	c.imag = ((f->counter.y * f->zoom) / (HEIGHT / 2)) - (f->zoom + f->srate.y);
	z = (t_cn){.real = 0, .imag = 0};
	i = -1;
	in_color = BLACK;
	if (f->fractal == MANDELBROT)
		mandelbrot(f, z, c, &i);
	else if (f->fractal == JULIA)
		julia(f, c, &i);
	if (i == f->maxiter)
		put_pixel_in_img(f, f->counter.x, f->counter.y, in_color);
	else
		put_pixel_in_img(f, f->counter.x, f->counter.y, f->color * i);
}

void	init_img(t_fractal *f)
{
	int		bpp;
	int		sizeline;
	int		endian;

	f->img.image = mlx_new_image(f->img.mlx, WIDTH, HEIGHT);
	f->img.data = mlx_get_data_addr(f->img.image, &bpp, &sizeline, &endian);
	f->img.bpp = bpp;
	f->img.sizeline = sizeline;
	f->img.endian = endian;
}

void	put_pixel_in_img(t_fractal *f, int x, int y, int color)
{
	char	*dst;

	dst = f->img.data + (y * f->img.sizeline + x * (f->img.bpp / 8));
	*(unsigned int *)dst = color;
}

size_t	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
