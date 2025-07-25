/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 15:21:24 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/07/25 14:07:55 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <string.h> // todo: remove for strdup

// TODO: gets input from parser
static char *maze_map[] = {
	"111111111111111111111111111111111111",
	"100000000000000000000000000000000001",
	"100000000000000000000000000000000001",
	"100000000000000000000000000000000001",
	"100000000000000000000000000000000001",
	"100000000000000000000000000000000001",
	"100000000000000000000000000000000001",
	"100000000000000000000000000000000001",
	"100000000000000000000000111100000001",
	"100000000000000000000000000000000001",
	"100000000000000000000000000000000001",
	"100000000000000011111000000000000001",
	"100000000000000000000000000000000001",
	"1000000000000000N0000000000000000111",
	"100000000000000000000000000000000001",
	"100000000000000000000000000000000001",
	"100000011110000000000000000000000001",
	"100000000001100000000000000000000001",
	"100000011110000000000000000000000001",
	"100000000000000000000000000000000001",
	"100000000000000000000000000000000001",
	"100000000000000000000000000000000001",
	"100000000000000000000000000000000001",
	"111111111111111111111111111111111111",
	NULL
};

int place_player(t_data *d)
{
	int x = 0;
	int y = 0;

	while (d->map[y])
	{
		x = 0;
		while (d->map[y][x])
		{
			if (d->map[y][x] == 'N')
			{
				d->player_x = x * TILE_SIZE;
				d->player_y = y * TILE_SIZE;
				d->map[y][x] = '0'; // Clear the player position in the map
				return (0);
			}
			x++;
		}
		y++;
	}
	write(2, "No player start (N) found in map\n", 33);
	return (1); // Player not found in map
}

// TODO:  protect on all
static char **copy_map(char **map)
{
	int i = 0;
	while (map[i])
		i++;

	char **copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return NULL;
	for (int j = 0; j < i; j++)
		copy[j] = strdup(map[j]);
	copy[i] = NULL;
	return copy;
}


int	init_data(t_data *d)
{
	d->mlx = mlx_init();
	if (!d->mlx)
		return (1);
	d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!d->win)
		return (1);
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->img)
		return (1);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->line_length, &d->endian);
	if (!d->addr)
		return (1);
	d->map = copy_map(maze_map);
	if (!d->map)
	{
		write(2, "Map initialization failed\n", 26);
		return (1);
	}
	if (place_player(d))
		return (1);
	return (0);
}
