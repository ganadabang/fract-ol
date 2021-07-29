#ifndef FRACT_H
# define FRACT_H

#include "../lib/minilibx_opengl_20191021/mlx.h"
#include "../lib/libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define X 600
#define Y 400


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

int		*setbound(int start1, int stop1, int start2, int stop2);
int		map(int	value, int *bound);

#endif
