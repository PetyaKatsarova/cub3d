
#include "../include/cub3d.h"

static void draw_tile(t_data *d, int x, int y, uint32_t color, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int px = x + j; // pixel x coordinate
			int py = y + i;
			if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
			{
				((int *)d->addr)[py * (d->line_length / 4) + px] = color;
			}
		}
	}
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
				draw_tile(d, x * TILE_SIZE, y * TILE_SIZE, WALL_COLOR, TILE_SIZE);
			else if (d->map[y][x] == '0')
				draw_tile(d, x * TILE_SIZE, y * TILE_SIZE, FLOOR_COLOR, TILE_SIZE);
			x++;
		}
		y++;
	}
	draw_tile(d, d->pl->x, d->pl->y, pl_COLOR, PL_SIZE);
}
