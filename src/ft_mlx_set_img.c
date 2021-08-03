#include "../include/fract.h"

void	ft_mlx_set_img(int x, int y, void *mlx, t_img *img)
{
	img->img = mlx_new_image(mlx, x, y);
	img->addr = mlx_get_data_addr(\
	img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
}
