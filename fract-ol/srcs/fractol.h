/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:19:14 by rturker           #+#    #+#             */
/*   Updated: 2022/11/20 12:35:49 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIDTH 1200
# define HEIGHT 1400
# define MAX 80
# define TITLE "fract ol"
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

# include "../mlxlib/mlx.h"
# include "colors.h"
# include <unistd.h>
# include <math.h>
# include <stdlib.h>

enum	e_fractal
{
	MANDELBROT,
	JULIA
};
typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;
typedef struct s_st
{
	int	f;
	int	s;
	int	t;
}	t_st;
typedef struct s_cn
{
	double	real;
	double	imag;
}	t_cn;
typedef struct s_counter
{
	int	x;
	int	y;
}	t_counter;
typedef struct scroll_rate
{
	float	x;
	float	y;
}	t_sr;
typedef struct s_image
{
	void	*mlx;
	void	*win;
	int		*image;
	char	*data;
	int		bpp;
	int		sizeline;
	int		endian;
}	t_image;
typedef struct s_fractal
{
	enum e_fractal		fractal;
	t_image				img;
	int					maxiter;
	t_counter			counter;
	double				zoom;
	int					color;
	t_cn				j;
	t_sr				srate;
	t_rgb				rgb;
	int					rgbarr[9];
	double				juliar[4];
	double				juliai[4];
	double				rc;
}	t_fractal;

void	ft_putendl_fd(char *s, int fd);
void	init_img(t_fractal *f);
void	init_fset(t_fractal *f);
int		init_variables(t_fractal *f);
void	fractal(t_fractal *f);
void	draw(t_fractal *f);
void	put_pixel_in_img(t_fractal *f, int x, int y, int color);
void	mandelbrot(t_fractal *f, t_cn z, t_cn c, int *i);
void	julia(t_fractal	*f, t_cn z, int *i);
void	phoenix(t_fractal *f, t_cn z, t_cn c, int *i);
int		ft_rgb2hex(t_rgb rgb);
int		fractal_hooks(int keycode, t_fractal *f);
void	nextpalet(t_fractal *f);
size_t	ft_strcmp(char *s1, char *s2);
void	init_rgb(t_fractal *f);
void	change_julia(t_fractal *f);
void	init_juliari(t_fractal *f);
int		zoom(int button, int x, int y, t_fractal *f);
void	exitwin(int keycode, t_fractal *f);

#endif