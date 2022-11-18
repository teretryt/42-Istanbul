/*
#include "fractol.h"
			
void	fractal(t_fractal *f)
{
	t_rgb cs;

	f->offset.x = ((WIDTH / 2) / (f->zoom / 2)) / -2;
	f->offset.y = ((HEIGHT / 2) / (f->zoom) / 2) / -2;
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
	t_cn			z;
	t_cn			c;
	int			i;
	unsigned int		in_color;

	c.real = f->counter.x / f->zoom + f->offset.x;
	c.imag = f->counter.y / f->zoom + f->offset.y;
	z = (t_cn) {.real = 0, .imag = 0};
	i = -1;
	in_color = (f->color != 5) ? CRIMSON : BLACK;
	if (f->fractal == MANDELBROT)
		mandelbrot(f, z, c, &i);
	else if (f->fractal == JULIA)
		julia(f, c, &i);
	else if (f->fractal == PHOENIX)
	{
		in_color = 0xffffff;
		phoenix(d, z, c, &i);
	}
	(i == f->maxIter) ? put_pixel_in_img(f, f->counter.x, f->counter.y, in_color) :
		put_pixel_in_img(d, d->i.x, d->i.y, ft_rgb2hex((t_rgb) {.r = i % 256 * 6, .g= i % 256, .b= i % 256}));
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
	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
		*(int *)&f->img.data[(x * f->img.bpp >> 3) +
			(y * f->img.sizeline)] = color;
}*/
