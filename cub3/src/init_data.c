#include "../include/cub3d.h"

// TODO: gets input from parser
char *maze_map[] = {
	"111111",
	"100001",
	"101101",
	"100001",
	"111111",
	NULL
};

int	init_data(t_data *d)
{
	d->mlx = mlx_init(WIDTH, HEIGHT, "COOL_CUB3D", true);
	if (!d->mlx)
		return (1);
	d->wall_img = NULL;
	d->floor_img = NULL;
	d->x = WIDTH / 2;
	d->y = HEIGHT / 2;
	d->map = maze_map;
	return (0);
}
