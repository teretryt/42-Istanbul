/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:13:22 by rturker           #+#    #+#             */
/*   Updated: 2022/11/21 09:42:14 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	fractal_hooks(int keycode, t_fractal *f)
{
	if (keycode == 124)
		f->srate.x += f->rc;
	else if (keycode == 123)
		f->srate.x -= f->rc;
	else if (keycode == 125)
		f->srate.y += f->rc;
	else if (keycode == 126)
		f->srate.y -= f->rc;
	else if (keycode == 8)
		nextpalet(f);
	else if (keycode == 38)
		change_julia(f);
	else if (keycode == 53)
		exit(0);
	fractal(f);
	return (1);
}

void	exitwin(int keycode, t_fractal *f)
{
	exit(0);
}

int	zoom(int button, int x, int y, t_fractal *f)
{
	(void)x;
	(void)y;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		if (button == MOUSE_SCROLL_UP)
			f->zoom *= 0.80;
		else
			f->zoom *= 1.20;
		fractal(f);
	}
	return (1);
}
