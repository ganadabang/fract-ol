#include "../include/fract.h"

void	set_mlx_img(void *mlx, t_data *img)
{
	img->img = mlx_new_image(mlx, X, Y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								 &img->endian);
}