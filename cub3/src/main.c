
#include "../include/cub3d.h"

int	main(void)
{
	t_data	data;

	if (init_data(&data))
		return (1);
	if (load_images(&data))
		return (1);
	draw_maze(&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx); // todo: clean more
	return (0);
}
