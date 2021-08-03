#include "../include/fract.h"

int	main(int ac, char *av[])
{
	t_data	data;

	init_data(&data, ac, av);
	create_fractal(&data, 1, 0, 0);
	listen_event(&data);
}
