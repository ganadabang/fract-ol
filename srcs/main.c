#include "../include/fract.h"

int	mandelbrot2(double n, double a, double b)
{
	const double	ca = a;
	const double	cb = b;
	double	aa;
	double	bb;
	int		rgb;

	rgb = create_trgb(0, 255, 255, 255);
	while (n++ < 200)
	{
		aa = a * a - b * b;
		bb = 2 * a * b;
		a = aa + ca;
		b = bb + cb;
		if (fabs(a + b) > 4)
		{
			if (n < 15)
				rgb = create_trgb(0, 120, 140, 120);
			else if (n < 20)
				rgb = create_trgb(0, map(n, setbound(15, 20, 120, 0)),\
									map(n, setbound(15, 20, 140, 255)),
									map(n, setbound(15, 20, 120, 255)));
			else if (n < 200)
				rgb = create_trgb(0, map(n, setbound(30, 100, 250, 150)),\
									map(n, setbound(30, 100, 255, 89)),\
									map(n, setbound(30, 100, 255, 10)));
			break ;
		}
		else if (n == 200)
			rgb = create_trgb(0, 0, 0, 0);
	}
	return (rgb);
}

void	get_img(t_data *data)
{
	double a;
	double b;
	double x;
	double y;
	int	rgb;
	int n;
	double	shift_x;
	double	shift_y;
	double	move_x;
	double	move_y;

	move_x = (long double)data->i * (long double)(data->x_max - data->x_min) / (long double)X + (long double)data->x_min;
	move_y = (long double)data->j * (long double)(data->y_max - data->y_min) / (long double)Y + (long double)data->y_min;

	data->x_min = data->x_min * data->zoom + move_x * (1 - data->zoom);
	data->x_max = data->x_max * data->zoom + move_x * (1 - data->zoom);
	data->y_min = data->y_min * data->zoom + move_y * (1 - data->zoom);
	data->y_max = data->y_max * data->zoom + move_y * (1 - data->zoom);

	x = 0;
	while (x < X)
	{
		y = 0;
		while (y < Y)
		{
			
			a = map(x, setbound(0, X, data->x_min, data->x_max));
			b = map(y, setbound(0, Y, data->y_min, data->y_max));
			ft_mlx_pixel_put(&data->img, x, y, mandelbrot2(n, a, b));
			if (a == 0 && b == 0)
				ft_mlx_pixel_put(&data->img, x, y, create_trgb(0, 255, 255, 255));
			y++;
		}
		x++;
	}
}

void	validate_parameter(int ac, char *av[])
{
	if (ac == 2 && ft_strncmp(av[1], "mandelbrot", 11) == 0)
		return ;
	if (ac ==3 && ft_strncmp(av[1], "julia", 5) == 0) 
		return ;
	ft_putstr_fd("usage: ./fractol [mandelbrot] \
	[julia 'real number' 'imaginary number']\n", 2);
	exit (0);
}

void	mandelbrot(t_data *data)
{
	printf("mandelbrot\n");
	get_img(data);
}

void	julia(t_data *data)
{
	printf("julia\n");
}

void	create_fractal(t_data *data)
{
	if (ft_strncmp(data->set, "mandelbrot", 11) == 0)
		mandelbrot(data);
	else if (ft_strncmp(data->set, "julia", 5) == 0)
		julia(data);
}

int	esc(int	keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_image(data->mlx, data->img.img);
		exit(0);
	}
	if (keycode >= 123 && keycode <= 126)
	{
		if (keycode == LEFT)
			data->x -= 50;
		if (keycode == RIGHT)
			data->x += 50;
		if (keycode == UP)
			data->y -= 50;
		if (keycode == DOWN)
			data->y += 50;
		printf("zoom:%lf x:%lf y%lf", data->zoom, data->x, data->y);
		create_fractal(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	}
	
	return (0);
}

int	zoom(int button, int x, int y, t_data *data)
{
	static float	count = 0;

	if ((button == WHEELUP || button == WHEELDOWN))
	{
		if (button == WHEELUP)
		{
			data->zoom = 0.96;
			data->i = x;
			data->j = y;
			count++;
		}
		else if (button == WHEELDOWN)
		{
			data->zoom = 1.04;
			data->i = x;
			data->j = y;
			count--;
		}
		if (count == 0)
			data->zoom = 1.0;
		create_fractal(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_data	data;

	validate_parameter(ac, av);
	
	//data_init;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, X, Y, av[1]);
	data.x = 0;
	data.y = 0;
	data.i = 0;
	data.j = 0;
	data.x_min = -2;
	data.x_max = 1;
	data.y_min = -1;
	data.y_max = 1;
	data.zoom = 1;

	data.set = av[1];
	ft_mlx_set_img(X, Y, data.mlx, &data.img);
	create_fractal(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
	//event hook
	mlx_mouse_hook(data.win, zoom, &data);
	mlx_key_hook(data.win, esc, &data);
	//loop
	mlx_loop(data.mlx);
}
