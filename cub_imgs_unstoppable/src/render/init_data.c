/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:21:24 by pekatsar          #+#    #+#             */
/*   Updated: 2025/08/08 14:31:52 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include <string.h> // todo: remove for strdup

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

int init_btns(t_btns *btns)
{
	btns->w = 0;
    btns->a = 0;
    btns->s = 0;
    btns->d = 0;
	btns->left_arrow = 0;
    btns->right_arrow = 0;
	return (0);
}

int	init_data(t_data *d, t_pl *pl, t_game_configs *game_configs)
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
		// 
	d->map = game_configs->map;
	if (!d->map)
	{
		write(2, "Map initialization failed\n", 26);
		return (1);
	}
	// d->needs_redraw = 0;
	d->pl = pl;
	if (place_pl(d))
		return (1);
	init_btns(&d->btns);
	init_textures(d, game_configs);
	return (0);
}
