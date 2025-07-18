#include "../include/cub3d.h"

int	load_images(t_data *d)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png("resources/brickWall.png");
	if (!tex)
		return (write(2, "Failed to load brickWall.png\n", 24), 1);
	d->wall_img = mlx_texture_to_image(d->mlx, tex);
	mlx_delete_texture(tex);
	if (!d->wall_img)
		return (1);

	tex = mlx_load_png("resources/dungeonFloor.png");
	if (!tex)
		return (write(2, "Failed to load floor.png\n", 25), 1);
	d->floor_img = mlx_texture_to_image(d->mlx, tex);
	mlx_delete_texture(tex);
	if (!d->floor_img)
		return (1);
	return (0);
}

void	draw_maze(t_data *d)
{
	int				x;
	int				y;
	mlx_image_t		*img;

	y = 0;
	while (d->map[y])
	{
		x = 0;
		while (d->map[y][x])
		{
			if (d->map[y][x] == '1')
				img = d->wall_img;
			else
				img = d->floor_img;
			mlx_image_to_window(d->mlx, img, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}
