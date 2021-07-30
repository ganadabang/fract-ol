#include "../include/fract.h"

void	make_gradient(t_win *win)
{
	int	x, y, r, g, b;

	x = 0;
	y = 0;
	while (y < Y)
	{
		x = 0;
		g = map(x, setbound(0, X, 0, 255));
		b = map(y, setbound(0, Y, 0, 255));
		r = 255;
		while (x < X)
		{
			r = map(x, setbound(0, X, 0, 255));
			ft_mlx_pixel_put(&win->img, x, y, create_trgb(0, r, g, b));
			x++;
		}
		y++;
	}
}

int	mandelbrot_set(t_win *win, double n, double a, double b)
{
	const double	ca = a;
	const double	cb = b;
	double	aa;
	double	bb;
	int		rgb;

	rgb = create_trgb(0, 255, 255, 255);
	while (n++ < 1000)
	{
		aa = a * a - b * b;
		bb = 2 * a * b;
		a = aa + ca;
		b = bb + cb;
		if (fabs(a + b) > 16)
		{
			if (n < 15)
				rgb = create_trgb(0, 120, 140, 120);
			else if (n < 30)
				rgb = create_trgb(0, map(n, setbound(15, 30, 120, 0)),\
									map(n, setbound(15, 30, 140, 255)),
									map(n, setbound(15, 30, 120, 255)));
			else if (n < 1000)
				rgb = create_trgb(0, map(n, setbound(30, 1000, 250, 255)),\
									map(n, setbound(30, 1000, 255, 215)),\
									map(n, setbound(30, 1000, 255, 0)));
			break ;
		}
		else if (n == 1000)
			rgb = create_trgb(0, 0, 0, 0);
	}
	return (rgb);
}

void	get_img(t_win *win)
{
	double a;
	double b;
	double x;
	double y;
	int	rgb;
	int n;

	x = 0;
	while (x < X)
	{
		y = 0;
		while (y < Y)
		{
			n = 0;
			a = map(x, setbound(0, X, -2.0, 1.0));
			b = map(y, setbound(0, Y, -1.0, 1.0));
			ft_mlx_pixel_put(&win->img, x, y, mandelbrot_set(win, n, a, b));
			y++;
		}
		x++;
	}
}

int mouse_get(t_win *win)
{
    int x;
    int y;

    mlx_mouse_get_pos(win->addr, &x, &y);
    printf("(%d, %d)\n", x, y);
    return (0);
}

int	button(int button, int x, int y, void *param)
{
	printf("button :%d\nx:%d\ny:%d\n", button, x, y);
	return (0);
}

typedef struct s_var
{
	void	*mlx;
	t_win	win;
}				t_var;

int	esc(int	keycode, t_var *var)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(var->mlx, var->win.addr);
		mlx_destroy_image(var->mlx, var->win.img.img);
		exit(0);
	}
	return (0);
}


int	main(void)
{
	t_var	var;

	var.mlx = mlx_init();
	var.win.addr = mlx_new_window(var.mlx, X, Y, "fract'ol");
	set_mlx_img(X, Y, var.mlx, &var.win.img);
	get_img(&var.win);
	mlx_put_image_to_window(var.mlx, var.win.addr, var.win.img.img, 0, 0);
	mlx_mouse_hook(var.win.addr, button, NULL);
	mlx_key_hook(var.win.addr, esc, &var);
	mlx_loop(var.mlx);
}
