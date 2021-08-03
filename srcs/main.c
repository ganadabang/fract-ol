#include "../include/fract.h"

int	validate_parameter(int ac, char *av[])
{
	if (ac == 2 && ft_strncmp(av[1], "mandelbrot", 11) == 0)
		return (MANDEL);
	if (ac == 2 && ft_strncmp(av[1], "ship", 5) == 0)
		return (SHIP);
	if (ac == 4 && ft_strncmp(av[1], "julia", 5) == 0) 
		return (JULIA);
	ft_putstr_fd("usage: ./fractol [mandelbrot] \
	[julia 'real number' 'imaginary number']\n", 2);
	exit (0);
}

int		calculate_ship(double a, double b, double ca, double cb)
{
	double			aa;
	double			bb;
	int				n;

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
			{
				return (create_trgb(0, \
						map(n, setbound(0, sqrt(ITER), 255, 0)), 109, 211));
			}
			else 
			{
				return (create_trgb(0, \
						map(n, setbound(0, sqrt(ITER), 255, 0)), 0, 0));
			}
			break ;
		}
	}
	return (create_trgb(0, 0, 0, 0));
}

int		calculate_trgb(double a, double b, double ca, double cb)
{
	double			aa;
	double			bb;
	int				n;

	n = -1;
	while (++n < ITER)
	{
		aa = pow(a, 2) - pow(b, 2);
		bb = 2 * a * b;
		a = aa + ca;
		b = bb + cb;
		if (fabs(a + b) > 8)
		{
			if (n < 100)
			{
				return (create_trgb(0, \
						map(n, setbound(0, sqrt(ITER), 255, 0)), 109, 211));
			}
			else 
			{
				return (create_trgb(0, \
						map(n, setbound(0, sqrt(ITER), 255, 0)), 211, 0));
			}
			break ;
		}
	}
	return (create_trgb(0, 255, 255, 255));
}

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

	shift_x = (c->rmax - c->rmin) / 5.f;
	shift_y = (c->imax - c->imin) / 5.f;
	c->rmin -= shift_x * data->shift_x;
	c->rmax -= shift_x * data->shift_x;
	c->imin -= shift_y * data->shift_y;
	c->imax -= shift_y * data->shift_y;
	data->shift_x = 0;
	data->shift_y = 0;
}

void	init_c(t_c *c)
{
	c->rmin = -1.5;
	c->rmax = 1.5;
	c->imin = -1;
	c->imax = 1;
}

void	ship(t_data *data, double zoom, int mouse_x, int mouse_y)
{
	int			i;
	int			j;
	double		a;
	double		b;
	static t_c	c;
	static int cnt = 0;
	
	i = -1;
	if (!cnt++)
		init_c(&c);
	apply_zoom(&c, zoom, mouse_x, mouse_y);
	apply_shift(&c, data);
	while (++i < WIN_WIDTH)
	{
		j = -1;
		while (++j < WIN_HEIGHT)
		{
			a = map(i, setbound(0, WIN_WIDTH, c.rmin, c.rmax));
			b = map(j, setbound(0, WIN_HEIGHT, c.imin, c.imax));
			ft_mlx_pixel_put(&data->img, i, j, \
							calculate_ship(a, b, a, b));
		}
	}	
}

void	julia(t_data *data, double zoom, int mouse_x, int mouse_y)
{
	int			i;
	int			j;
	double		a;
	double		b;
	static t_c	c;
	static int cnt = 0;
	
	if (!cnt++)
		init_c(&c);
	i = -1;
	apply_zoom(&c, zoom, mouse_x, mouse_y);
	apply_shift(&c, data);
	while (++i < WIN_WIDTH)
	{
		j = -1;
		while (++j < WIN_HEIGHT)
		{
			a = map(i, setbound(0, WIN_WIDTH, c.rmin, c.rmax));
			b = map(j, setbound(0, WIN_HEIGHT, c.imin, c.imax));
			ft_mlx_pixel_put(&data->img, i, j, \
							calculate_trgb(a, b, data->a, data->b));
		}
	}	
}

void	mandelbrot(t_data *data, double zoom, int mouse_x, int mouse_y)
{
	int			i;
	int			j;
	double		a;
	double		b;
	static t_c	c;
	static int cnt = 0;
	
	i = -1;
	if (!cnt++)
		init_c(&c);
	apply_zoom(&c, zoom, mouse_x, mouse_y);
	apply_shift(&c, data);
	while (++i < WIN_WIDTH)
	{
		j = -1;
		while (++j < WIN_HEIGHT)
		{
			a = map(i, setbound(0, WIN_WIDTH, c.rmin, c.rmax));
			b = map(j, setbound(0, WIN_HEIGHT, c.imin, c.imax));
			ft_mlx_pixel_put(&data->img, i, j, \
							calculate_trgb(a, b, a, b));
		}
	}	
}

void	init_data(t_data *data, int ac, char *av[])
{
	data->settype = validate_parameter(ac, av);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, av[1]);
	ft_mlx_set_img(WIN_WIDTH, WIN_HEIGHT, data->mlx, &data->img);
	data->a = 0;
	data->b = 0;
	data->shift_x = 0;
	data->shift_y = 0;
	if (data->settype == JULIA)	
	{
		data->a = atof(av[2]);
		data->b = atof(av[3]);
	}
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

int	mouse_event(int button, int x, int y, t_data *data)
{
	static double zoom = 1;

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

int	key_event(int keycode, t_data *data)
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
			data->shift_x = -1;
		else if (keycode == RIGHT)
			data->shift_x = 1;
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

int	main(int ac, char *av[])
{
	t_data	data;

	init_data(&data, ac, av);
	create_fractal(&data, 1, 0, 0);
	listen_event(&data);
}
