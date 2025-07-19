#include "../include/cub3d.h"

static void draw_tile(t_data *d, uint32_t color)
{
	mlx_image_t *tile = mlx_new_image(d->mlx, TILE_SIZE, TILE_SIZE);
	if (!tile)
		return;
	for (int i = 0; i < TILE_SIZE; i++)
	{
		for (int j = 0; j < TILE_SIZE; j++)
			mlx_put_pixel(tile, j, i, color);
	}
	//mlx_image_to_window(d->mlx, tile, x * TILE_SIZE, y * TILE_SIZE);
}

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
				draw_tile(d, x, y, WALL_COLOR);
			else if (d->map[y][x] == '0')
				draw_tile(d, x, y, FLOOR_COLOR);
			else if (d->map[y][x] == 'N')
			{
				// TODO FOR PLAYER
			};
			mlx_image_to_window(d->mlx, img, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}
