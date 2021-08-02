#ifndef FRACT_H
# define FRACT_H

#include "../lib/minilibx_opengl_20191021/mlx.h"
#include "../lib/libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

//size
# define X 900
# define Y 600
//button
# define WHEELUP 4
# define WHEELDOWN 5
//keycode
# define ESC 53
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define UP 126

# define ITER 1000
# define MANDEL	1
# define JULIA	2
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
}				t_data;

typedef struct s_color
{
	int	r;
	int g;
	int b;
}				t_color;

# define WIN_WIDTH 900
# define WIN_HEIGHT 600


void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);
void	ft_mlx_set_img(int x, int y, void *mlx, t_img *img);

int		create_trgb(int t, int r, int g, int b);

double	*setbound(double start1, double stop1, double start2, double stop2);
double	map(double value, double *bound);

#endif
