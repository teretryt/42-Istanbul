/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 11:58:35 by rturker           #+#    #+#             */
/*   Updated: 2022/11/21 09:48:50 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	init_variables(t_fractal *f)
{
	f->img.mlx = mlx_init();
	if (!(f->img.mlx))
		ft_putendl_fd("Mlx olusturulamadi\n", 1);
	f->img.win = mlx_new_window(f->img.mlx, WIDTH, HEIGHT, TITLE);
	if (!(f->img.win))
		ft_putendl_fd("Pencere olusturulamadi.\n", 1);
	init_img(f);
	if (!f->img.image)
		ft_putendl_fd("Resim olu�turulamad�\n", 1);
	init_rgb(f);
	init_juliari(f);
	f->rc = 0.1;
	f->zoom = 3;
	f->srate.x = 0;
	f->srate.y = 0;
	f->color = ft_rgb2hex(f->rgb);
	init_fset(f);
	return (1);
}

int	init_fractal(t_fractal *f, char *name)
{
	if (!ft_strcmp(name, "Mandelbrot"))
		f->fractal = MANDELBROT;
	else if (!ft_strcmp(name, "Julia"))
		f->fractal = JULIA;
	else
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_fractal	f;
	int			infc;
	int			invc;

	if (ac != 2 || !(init_fractal(&f, av[1])))
	{
		ft_putendl_fd("[Mandelbrot] [Julia]\n", 1);
		return (-1);
	}
	invc = init_variables(&f);
	if (!invc)
	{
		ft_putendl_fd("Değişkenler dahil edilemedi.s", 1);
		return (-1);
	}
	fractal(&f);
	mlx_hook(f.img.win, 2, 1L << 0, fractal_hooks, &f);
	mlx_hook(f.img.win, 4, 0, zoom, &f);
	mlx_hook(f.img.win, 17, 1L << 2, exitwin, &f);
	mlx_loop(f.img.mlx);
	return (0);
}
