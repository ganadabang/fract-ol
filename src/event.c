#include "../include/fract.h"

static int	mouse_event(int button, int x, int y, t_data *data)
{
	if ((button == WHEELUP || button == WHEELDOWN))
	{
		if (button == WHEELUP)
		{
			create_fractal(data, 0.96, x, y);
		}
		else if (button == WHEELDOWN)
		{
			create_fractal(data, 1.04, x, y);
		}
	}
	return (0);
}

static int	key_event(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(data->mlx, data->img.img);
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	if (keycode >= LEFT || keycode <= UP)
	{
		if (keycode == LEFT)
			data->shift_x = 1;
		else if (keycode == RIGHT)
			data->shift_x = -1;
		else if (keycode == DOWN)
			data->shift_y = -1;
		else if (keycode == UP)
			data->shift_y = 1;
		create_fractal(data, 1, 0, 0);
	}
	return (0);
}

void	listen_event(t_data *data)
{
	mlx_mouse_hook(data->win, mouse_event, data);
	mlx_key_hook(data->win, key_event, data);
	mlx_loop(data->mlx);
}
