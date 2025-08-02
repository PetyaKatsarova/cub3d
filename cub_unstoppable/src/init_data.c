/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 15:21:24 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/02 16:47:01 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include <string.h> // todo: remove for strdup

// TODO: gets input from parser; 24 cols, 34 len(width)
//static char *maze_map[] = {
//	"111111111111111111111111111111111111",
//	"100000000000000000000000000000000001",
//	"100000000000000000000000000000000001",
//	"100000000000000000000000000000000001",
//	"100000000000000000000000000000000001",
//	"100000000000000000000000000000000001",
//	"100000000000000000000000000000000001",
//	"100000000000000000000000000000000001",
//	"100000000000000000000000111100000001",
//	"100000000000000000000000000000000001",
//	"100000000000000000000000000000000001",
//	"100000000000000011111000000000000001",
//	"100000000000000000000000000000000001",
//	"1000000000000000E0000000000000000111",
//	"100000000000000000000000000000000001",
//	"100000000000000000000000000000000001",
//	"100000011110000000000000000000000001",
//	"100000000001100000000000000000000001",
//	"100000011110000000000000000000000001",
//	"100000000000000000000000000000000001",
//	"100000000000000000000000000000000001",
//	"100000000000000000000000000000000001",
//	"100000000000000000000000000000000001",
//	"111111111111111111111111111111111111",
//	NULL
//};

static char *maze_map[] = {
    "11111111",
    "10000001",
    "10111001",
    "10001001",
    "100N001",
    "10111001",
    "10000001",
    "11111111",
//	"1111111111111111111111111",
//"1000000000110000000000001",
//"1011000001110000000000001",
//"1001000000000000000000001",
//"111111111011000001110000000000001",
//"100000000011000001110111111111111",
//"11110111111111011100000010001",
//"11110111111111011101010010001",
//"11000000110101011100000010001",
//"100000000000N0001100000010001",
//"10000000000000001101010010001",
//"11000001110101011111011110N0111",
//"11110111 1110101 101111010001",
//"11111111 1111111 111111111111",
    NULL
};

static int place_pl(t_data *d)
{
	int x = 0;
	int y = 0;

	while (d->map[y]) // cols
	{
		x = 0;
		while (d->map[y][x]) // rows
		{
			if (d->map[y][x] == 'N') // hard coded: TODO from parser
			{
				if (init_pl(d->pl, x * TILE_SIZE, y * TILE_SIZE, 'N'))
					return (write(2, "Failed to initialize pl\n", 28), 1);
				return (d->map[y][x] = '0', 0); // Clear the pl position in the map
			}
			else if (d->map[y][x] == 'E')
			{
				if (init_pl(d->pl, x * TILE_SIZE, y * TILE_SIZE, 'E'))
					return (write(2, "Failed to initialize pl\n", 28), 1);
				return (d->map[y][x] = '0', 0); // Clear the pl position in the map
			}
			else if (d->map[y][x] == 'W')
			{
				if (init_pl(d->pl, x * TILE_SIZE, y * TILE_SIZE, 'W'))
					return (write(2, "Failed to initialize pl\n", 28), 1);
				return (d->map[y][x] = '0', 0); // Clear the pl position in the map
			}
			else if (d->map[y][x] == 'S')
			{
				if (init_pl(d->pl, x * TILE_SIZE, y * TILE_SIZE, 'S'))
					return (write(2, "Failed to initialize pl\n", 28), 1);
				return (d->map[y][x] = '0', 0); // Clear the pl position in the map
			}
				
			x++;
		}
		y++;
	}
	return (write(2, "No pl start (N) found in map\n", 33), 1); // pl not found
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
		copy[j] = strdup(map[j]); // todo: wrtie ft_strdup and protect here
	copy[i] = NULL;
	return copy;
}


int	init_data(t_data *d, t_pl *pl)
{
	d->mlx = mlx_init();
	if (!d->mlx)
		return (1);
	d->win = mlx_new_window(d->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!d->win)
		return (1);
	d->img = mlx_new_image(d->mlx, WIN_WIDTH, WIN_HEIGHT);
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
	d->pl = pl;
	if (place_pl(d))
		return (1);
	return (0);
}
