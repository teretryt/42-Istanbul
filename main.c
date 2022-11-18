#include "fractol.h"

void	mandelbrot(t_fractal *f, t_cn z, t_cn c, int *i)
{
	double	temp;
	while (++(*i) < f->max && z.real * z.real + z.imag * z.imag < 4)
	{
		temp = z.real;
		z.real =  z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * temp * z.imag + c.imag;
	}
}

void	julia(t_fractal	*f, t_cn z, int *i)
{
	double	temp;
	while (++(*i) < f->max && z.real * z.real + z.imag * z.imag < 4)
	{
		temp = z.real;
		z.real =  z.real * z.real - z.imag * z.imag + (-0.6);
		z.imag = 2 * temp * z.imag + 0.4;
	}
}

void	phoenix(t_fractal *f, t_cn z, t_cn c, int *i)
{
	return;
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

int			mouse_scaling_hook(int k, int x, int y, t_fractal *f)
{
	float	scaling;

	scaling = 0;
	if ((k == 1 || k == 2 || k == 4 || k == 5) &&
	(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT))
	{
		if (k == 4 || k == 1)
			scaling = 1.25;
		else if (k == 5 || k == 2)
			scaling = 0.8;
		if (k == 1 || k == 2)
		{
			f->offset.x = (f->offset.x + ((WIDTH / 2) - x) * scaling);
			f->offset.y = (f->offset.y + ((HEIGHT / 2) - y) * scaling);
		}
		f->zoom *= scaling;
		fractal(f);
	}
	return (1);
}

void	init_fset(t_fractal *f)
{
	if (f->fractal == JULIA)
	{
		f->zoom = 300;
		f->max = 250;
		//dif_julia(f);
	}
	else if (f-> fractal == MANDELBROT)
	{
		f->zoom = 300;
		f->max = 250;
	}
	else if (f-> fractal == PHOENIX)
	{
		f->zoom = 80;
		f->max = 250;
	}
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

int	init_variables(t_fractal *f)
{
	if (!(f->img.mlx = mlx_init()))
		printf("Mlx oluþturulamadý\n");
	if (!(f->img.win = mlx_new_window(f->img.mlx, WIDTH, HEIGHT, TITLE)))
		printf("Pencere oluþturulamadý.\n");		
	init_img(f);
	if (!f->img.image)
		printf("Resim oluþturulamadý\n");
	f->zoom = 200;
	f->color = 0;
	init_fset(f);
	return (1);
}



int	init_fractal(t_fractal *f, char *name)
{
	if (!strcmp(name, "Mandelbrot"))
		f->fractal = MANDELBROT;
	else if (!strcmp(name, "Phoenix"))
		f->fractal = PHOENIX;
	else if (!strcmp(name, "Julia"))
		f->fractal = JULIA;
	else
		return (0);
	return (1);
}

void	fractal(t_fractal *f)
{
	t_rgb cs;

	f->min.x = ((f->offset.x + (WIDTH / 2)) / (f->zoom / 2)) / -2;
	f->min.y = ((f->offset.y + (HEIGHT / 2)) / (f->zoom / 2)) / -2;
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

	c.real = f->counter.x / f->zoom + f->min.x;
	c.imag = f->counter.y / f->zoom + f->min.y;
	z = (t_cn) {.real = 0, .imag = 0};
	i = -1;
	in_color = (f->color != 5) ? BLACK : CRIMSON;
	if (f->fractal == MANDELBROT)
		mandelbrot(f, z, c, &i);
	else if (f->fractal == JULIA)
		julia(f, c, &i);
	else if (f->fractal == PHOENIX)
	{
		in_color = 0xffffff;
		phoenix(f, z, c, &i);
	}
	(i == f->max) ? put_pixel_in_img(f, f->counter.x, f->counter.y, in_color) :
		put_pixel_in_img(f, f->counter.x, f->counter.y, ft_rgb2hex((t_rgb) {.r = i, .g= i, .b= i}));
}

void	put_pixel_in_img(t_fractal *f, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
		*(int *)&f->img.data[(x * f->img.bpp >> 3) +
			(y * f->img.sizeline)] = color;
}

int main(int ac, char **av)
{
	t_fractal	f;
	
	if (ac != 2 || !init_fractal(&f, av[1]))
	{
		printf("\033[32mUsage: ./fractol Fractal, i.e: ./fractol Barnsley\n");
		printf("[Mandelbrot] [Julia] [Phoenix]\n");
		exit(-1);
	}
	else if (!(init_variables(&f)))
		printf("Failed to initailize variables\n");
	
	fractal(&f);
	
	mlx_mouse_hook(f.img.win, mouse_scaling_hook, &f);
	mlx_loop(f.img.mlx);
	return (0);
}


