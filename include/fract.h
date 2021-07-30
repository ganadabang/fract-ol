#ifndef FRACT_H
# define FRACT_H

#include "../lib/minilibx_opengl_20191021/mlx.h"
#include "../lib/libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

//size
# define X 1280
# define Y 720
//button
# define WHEELUP 4
# define WHEELDOWN 5
//keycode
# define ESC 53
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define UP 126

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_win
{
	void	*addr;
	t_data	img;
}				t_win;

typedef struct s_color
{
	int	r;
	int g;
	int b;
}				t_color;

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);
void	set_mlx_img(int x, int y, void *mlx, t_data *img);

double	*setbound(double start1, double stop1, double start2, double stop2);
double	map(double value, double *bound);

#endif
