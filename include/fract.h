#ifndef FRACT_H
# define FRACT_H

#include "../lib/minilibx_opengl_20191021/mlx.h"
#include <unistd.h>
#include <stdlib.h>

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
