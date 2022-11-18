#ifndef FRACT_OL_H
# define FRACT_OL_H
# define WIDTH 1200
# define HEIGHT 900
# define MAX 80
# define TITLE "fract ol"


#include "colors.h"
#include "converts.h"
#include "mlx.h"
#include "mlx_int.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

enum e_fractal{
	MANDELBROT,
	JULIA,
	PHOENIX
};

typedef struct		s_cn
{
	double			real;
	double			imag;
}				t_cn;

typedef struct	s_counter
{
	int	x;
	int	y;
}	t_counter;

typedef struct	s_offset
{
	float	x;
	float	y;
}	t_offset;

typedef struct	s_image{
	void	*mlx;
	void	*win;
	int	*image;
	char	*data;
	int	bpp;
	int	sizeline;
	int	endian;
}	t_image;

typedef struct	s_fractal
{
	enum e_fractal		fractal;
	t_image			img;
	int			max;
	t_counter		min;
	t_offset		offset;
	t_counter		counter;
	double			zoom;
	int			color;
}	t_fractal;

void	ft_putendl_fd(char *s, int fd);
void	init_img(t_fractal *f);
void	init_fset(t_fractal *f);
int	init_variables(t_fractal *f);
void	fractal(t_fractal *f);

#endif
