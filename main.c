#include "fract.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		x;
	int		y;

	int r = 0;
	int g = 255;
	int b = 255;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 255, 255, "Hello world!");
	img.img = mlx_new_image(mlx, 255, 255);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	while (y <= 255)
	{
		x = 0;
		g++;
		b--;
		r = 255;
		while (x <= 255)
		{
			ft_mlx_pixel_put(&img, x, y, create_trgb(0, r, g, b));
			x++;
			r--;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}