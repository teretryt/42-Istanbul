/*#include "fractol.h"

void	init_fset(t_fractol *f)
{
	if (f->fractal == JULIA)
	{
		f->zoom = 100;
		f->max = 250;
		//dif_julia(f);
	}
	else if (f-> fractal == MANDELBROT)
	{
		f->zoom = 80;
		f->max = 250;
	}
	else if (f-> fractal == PHOENIX)
	{
		f->zoom = 80;
		f->max = 250;
	}
}
void	mandelbrot(t_fractal f, t_cn z, t_cn c, int *i)
{
	double	temp;
	while (++(*i) < f->maxIter && z.real * z.real + z.imag * z.imag < 4)
	{
		temp = z.real;
		z.real =  z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * temp * z.imag + c.imag;
	}
}

void	julia(t_fractal	f, t_cn z, int *i)
{
	double	temp;
	while (++(*i) < f->maxIter && z.real * z.real + z.imag * z.imag < 4)
	{
		temp = z.real;
		z.real =  z.real * z.real - z.imag * z.imag + j.real;
		z.imag = 2 * temp * z.imag + j.imag;
	}
}

void	phoenix(t_fractal f, t_cn z, t_cn c, int *i)
{
	return;
}
*/
