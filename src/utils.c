#include "../include/fract.h"

void	apply_zoom(t_c *c, double zoom, int x, int y)
{
	double	move_x;
	double	move_y;

	move_x = map(x, setbound(0, WIN_WIDTH, c->rmin, c->rmax));
	move_y = map(y, setbound(0, WIN_HEIGHT, c->imin, c->imax));
	c->rmin = c->rmin * zoom + (move_x * (1 - zoom));
	c->rmax = c->rmax * zoom + (move_x * (1 - zoom));
	c->imin = c->imin * zoom + (move_y * (1 - zoom));
	c->imax = c->imax * zoom + (move_y * (1 - zoom));
}

void	apply_shift(t_c *c, t_data *data)
{
	double	shift_x;
	double	shift_y;

	shift_x = (c->rmax - c->rmin) / 10.f;
	shift_y = (c->imax - c->imin) / 10.f;
	c->rmin -= shift_x * data->shift_x;
	c->rmax -= shift_x * data->shift_x;
	c->imin -= shift_y * data->shift_y;
	c->imax -= shift_y * data->shift_y;
	data->shift_x = 0;
	data->shift_y = 0;
}

void	create_fractal(t_data *data, double zoom, int mouse_x, int mouse_y)
{
	if (data->settype == MANDEL)
		mandelbrot(data, zoom, mouse_x, mouse_y);
	if (data->settype == JULIA)
		julia(data, zoom, mouse_x, mouse_y);
	if (data->settype == SHIP)
		ship(data, zoom, mouse_x, mouse_y);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
