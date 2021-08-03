#include "../include/fract.h"

int	calculate_ship(double a, double b, double ca, double cb)
{
	double	aa;
	double	bb;
	int		n;

	n = -1;
	while (++n < ITER)
	{
		aa = pow(a, 2) - pow(b, 2);
		bb = fabs(2 * a * b);
		a = aa + ca;
		b = bb + cb;
		if (fabs(a + b) > 100)
		{
			if (n < 100)
				return (create_trgb(0, \
					map(n, setbound(0, sqrt(ITER), 255, 0)), 109, 211));
			else
				return (create_trgb(0, \
					map(n, setbound(0, sqrt(ITER), 255, 0)), 0, 0));
			break ;
		}
	}
	return (create_trgb(0, 0, 0, 0));
}

void	ship(t_data *data, double zoom, int mouse_x, int mouse_y)
{
	int		i;
	int		j;
	double	a;
	double	b;

	i = -1;
	apply_zoom(&data->c, zoom, mouse_x, mouse_y);
	apply_shift(&data->c, data);
	while (++i < WIN_WIDTH)
	{
		j = -1;
		while (++j < WIN_HEIGHT)
		{
			a = map(i, setbound(0, WIN_WIDTH, data->c.rmin, data->c.rmax));
			b = map(j, setbound(0, WIN_HEIGHT, data->c.imin, data->c.imax));
			ft_mlx_pixel_put(&data->img, i, j, \
							calculate_ship(a, b, a, b));
		}
	}
}
