#include "../include/cub3d.h"

void	draw_maze(t_data *d)
{
	int				x;
	int				y;

	y = 0;
	while (d->map[y])
	{
		x = 0;
		while (d->map[y][x])
		{
			if (d->map[y][x] == '1')
				img = d->wall_img;
			else if (d->map[y][x] == '0')
				img = d->floor_img;
			mlx_image_to_window(d->mlx, img, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}
