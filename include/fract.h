#ifndef FRACT_H
# define FRACT_H

# include "../lib/minilibx_opengl_20191021/mlx.h"
# include "../lib/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define ITER 1000
//size
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
//button
# define WHEELUP 4
# define WHEELDOWN 5
//keycode
# define ESC 53
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define UP 126
//set_name
# define MANDEL	1
# define JULIA	2
# define SHIP	3

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_c {
	double	rmin;
	double	rmax;
	double	imin;
	double	imax;
	double	zoom;
}				t_c;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		settype;
	double	a;
	double	b;
	double	shift_x;
	double	shift_y;
	t_c		c;
}				t_data;

typedef struct s_color
{
	int	r;
	int g;
	int b;
}				t_color;


void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);
void	ft_mlx_set_img(int x, int y, void *mlx, t_img *img);
int		create_trgb(int t, int r, int g, int b);
double	*setbound(double start1, double stop1, double start2, double stop2);
double	map(double value, double *bound);
//data.c
void	init_data(t_data *data, int ac, char *av[]);
//event.c
void	listen_event(t_data *data);
//create.c
void	apply_zoom(t_c *c, double zoom, int x, int y);
void	apply_shift(t_c *c, t_data *data);
void	init_c(t_c *c);
void	create_fractal(t_data *data, double zoom, int mouse_x, int mouse_y);
void	mandelbrot(t_data *data, double zoom, int mouse_x, int mouse_y);
void	julia(t_data *data, double zoom, int mouse_x, int mouse_y);
void	ship(t_data *data, double zoom, int mouse_x, int mouse_y);
#endif
