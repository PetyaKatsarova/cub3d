#include "../include/cub3d.h"

//float px, py, pdx, pdy, pa
int draw_vector(t_data *d)
{
	double x = d->pl->x;
	double y = d->pl->y;
	double angle = d->pl->angle;

	for (int i = 0; i < 30; i++)
	{
		int px = (int)(x + cos(angle) * i);
		int py = (int)(y + sin(angle) * i);
		if (px >= 0 && px < (COLS * TILE_SIZE) && py >= 0 && py < (ROWS * TILE_SIZE))
			((int *)d->addr)[py * (d->line_length / 4) + px] = PURPLE;
	}
    return (0);
}
