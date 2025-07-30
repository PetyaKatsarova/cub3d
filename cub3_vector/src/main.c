/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 15:13:27 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/07/30 10:26:42 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int key_hook(int keycode, t_data *d)
{
	pl_control(d, keycode);
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
	t_pl 	pl;

	if (init_data(&data, &pl)) 
		return (1);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 17, 0, close_window, &data); // event code: 17 for x
	mlx_loop(data.mlx);
	// todo: clean more
	return (0);
}
