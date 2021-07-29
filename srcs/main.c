#include "../include/fract.h"

void	make_gradient(t_win *win)
{
	int	x;
	int	y;
	int r;
	int g;
	int b;

	x = 0;
	y = 0;
	while (y <= Y)
	{
		x = 0;
		g = map(x, setbound(0, X, 0, 255));
		b = map(y, setbound(0, Y, 0, 255));
		r = 255;
		while (x <= X)
		{
			r = map(x, setbound(0, X, 0, 255));
			ft_mlx_pixel_put(&win->img, x, y, create_trgb(0, r, g, b));
			x++;
		}
		y++;
	}
}

int	main(void)
{
	void	*mlx;
	t_win	win;

	mlx = mlx_init();
	win.addr = mlx_new_window(mlx, X, Y, "fract'ol");
	set_mlx_img(X, Y, mlx, &win.img);
	make_gradient(&win);
	mlx_put_image_to_window(mlx, win.addr, win.img.img, 0, 0);
	mlx_loop(mlx);
}
