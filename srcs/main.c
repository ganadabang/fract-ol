#include "../include/fract.h"

int	validate_parameter(int ac, char *av[])
{
	if (ac == 2 && ft_strncmp(av[1], "mandelbrot", 11) == 0)
		return (MANDEL);
	if (ac == 4 && ft_strncmp(av[1], "julia", 5) == 0) 
		return (JULIA);
	ft_putstr_fd("usage: ./fractol [mandelbrot] \
	[julia 'real number' 'imaginary number']\n", 2);
	exit (0);
}

int	key_event(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(data->mlx, data->img.img);
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	return (0);
}

int	mouse_event(int button, int x, int y, t_data *data)
{
	static float	count = 0;

	if ((button == WHEELUP || button == WHEELDOWN))
	{
		if (button == WHEELUP)
		{
			data->zoom = 0.04;
			data->i = x;
			data->j = y;
			count++;
		}
		else if (button == WHEELDOWN)
		{
			data->zoom = -0.4;
			data->i = x;
			data->j = y;
			count--;
		}
		if (count == 0)
			data->zoom = 1.0;
		create_fractal(data, x, y);
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	}
	return (0);
}

void	init_c(t_c *c)
{
	c->rmin = -2.0;
	c->rmax = 1.0;
	c->imin = -1.0;
	c->imax = 1.0;
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

void	julia(t_data *data, int mouse_x, int mouse_y)
{
	int			i;
	int			j;
	double		a;
	double		b;
	static t_c	c;
	
	init_c(&c);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		j = -1;
		while (++j < WIN_HEIGHT)
		{
			a = map(i, setbound(0, WIN_WIDTH, c.rmin, c.rmax));
			b = map(j, setbound(0, WIN_HEIGHT, c.imin, c.imax));
			ft_mlx_pixel_put(&data->img, i, j, calculate_trgb(a, b, data->a, data->b));
		}
	}	
}

void	mandelbrot(t_data *data, int mouse_x, int mouse_y)
{
	int			i;
	int			j;
	double		a;
	double		b;
	static t_c	c;
	
	init_c(&c);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		j = -1;
		while (++j < WIN_HEIGHT)
		{
			a = map(i, setbound(0, WIN_WIDTH, c.rmin, c.rmax));
			b = map(j, setbound(0, WIN_HEIGHT, c.imin, c.imax));
			ft_mlx_pixel_put(&data->img, i, j, calculate_trgb(a, b, a, b));
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
	if (data->settype == JULIA)	
	{
		data->a = atof(av[2]);
		data->b = atof(av[3]);
	}
}

void	create_fractal(t_data *data, int mouse_x, int mouse_y)
{
	if (data->settype == MANDEL)
		mandelbrot(data, mouse_x, mouse_y);
	if (data->settype == JULIA)
		julia(data, mouse_x, mouse_y);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
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
	create_fractal(&data, 0, 0);
	listen_event(&data);
}
