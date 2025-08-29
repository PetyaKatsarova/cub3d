/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 15:21:24 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/29 12:59:17 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	init_btns(t_btns *btns)
{
	btns->w = 0;
	btns->a = 0;
	btns->s = 0;
	btns->d = 0;
	btns->left_arrow = 0;
	btns->right_arrow = 0;
	return (0);
}

static	int	init_mlx_data(t_data	*d)
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
	d->addr = mlx_get_data_addr(d->img, &d->bpp,
			&d->line_length, &d->endian);
	if (!d->addr)
		return (1);
	return (0);
}

int	init_data(t_data *d, t_pl *pl, t_game_configs *game_configs)
{
	if (init_mlx_data(d) == 1)
		return (1);
	d->map = game_configs->map;
	if (!d->map)
		return (write(2, "Map initialization failed\n", 26), 1);
	d->game_configs = game_configs;
	if (!d->game_configs)
		return (write(2, "parse initialization failed\n", 28), 1);
	d->pl = pl;
	d->map_cols = game_configs->map_cols;
	d->map_rows = game_configs->map_rows;
	d->floor = game_configs->floor_argb;
	d->ceiling = game_configs->ceiling_argb;
	init_pl(pl, game_configs);
	init_btns(&d->btns);
	init_textures(d, game_configs);
	d->focus = true;
	return (0);
}

int	clean_mlx(t_data *d)
{
	if (!d)
		return (1);
	if (d->img && d->mlx)
		mlx_destroy_image(d->mlx, d->img);
	if (d->win && d->mlx)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
		d->mlx = NULL;
	}
	return (0);
}
