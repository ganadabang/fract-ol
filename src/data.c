#include "../include/fract.h"

static int	validate_parameter(int ac, char *av[])
{
	if (ac == 2 && ft_strncmp(av[1], "mandelbrot", 11) == 0)
		return (MANDEL);
	if (ac == 2 && ft_strncmp(av[1], "ship", 5) == 0)
		return (SHIP);
	if (ac == 4 && ft_strncmp(av[1], "julia", 5) == 0)
		return (JULIA);
	ft_putstr_fd("usage: ./fractol [mandelbrot]", 2);
	ft_putstr_fd(" julia 'real number' 'imaginary number'] [ship]\n", 2);
	exit (0);
}

void	init_c(t_c *c)
{
	c->rmin = -1.5;
	c->rmax = 1.5;
	c->imin = -1;
	c->imax = 1;
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
	init_c(&data->c);
}
