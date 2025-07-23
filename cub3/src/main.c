/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 15:13:27 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/07/23 17:06:33 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int key_hook(int keycode, t_data *d)
{
	player_control(d, keycode);
	draw_maze(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	return (0);
}

static int	close_window(void *param)
{
	(void)param;
	exit(0);
}

int	main(void)
{
	t_data	data;

	if (init_data(&data))
		return (1);
	draw_maze(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 17, 0, close_window, &data); // event code: 17 for x
	mlx_loop(data.mlx);
	//mlx_terminate(data.mlx); // todo: clean more
	return (0);
}
