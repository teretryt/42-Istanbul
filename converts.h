#include "colors.h"

int		ft_rgb2hex(t_rgb rgb)
{
	return (((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b);
}
