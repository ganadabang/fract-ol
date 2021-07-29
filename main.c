#include "./minilibx_opengl_20191021/mlx.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*title = "test";
	int		x;
	int		y;

	int r = 0;
	int g = 255;
	int b = 255;

	g = 0;
	x = 0;
	y = 0;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window (mlx_ptr, 255, 255, title);
	while (y <= 255)
	{
		x = 0;
		g++;
		b--;
		r = 255;
		while (x <= 255)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, create_trgb(0, r, g, b));
			x++;
			r--;
		}
		y++;
	}
	mlx_loop(mlx_ptr);
	return (0);
}