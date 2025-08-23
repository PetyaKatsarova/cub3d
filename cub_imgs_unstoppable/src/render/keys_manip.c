/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys_manip.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/22 14:31:58 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/23 14:48:37 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* sets button state to pressed */
int	key_press(int keycode, t_data *d)
{
	if (keycode == 'q' || keycode == ESC)
	{
		clean_mlx(d);
		free_game_configs(d->game_configs);
		exit(0);
	}
	if (keycode == 'w')
		d->btns.w = 1;
	else if (keycode == 'a')
		d->btns.a = 1;
	else if (keycode == 's')
		d->btns.s = 1;
	else if (keycode == 'd')
		d->btns.d = 1;
	else if (keycode == KEY_LEFT)
		d->btns.left_arrow = 1;
	else if (keycode == KEY_RIGHT)
		d->btns.right_arrow = 1;
	return (0);
}

/* sets button state to released */
int	key_release(int keycode, t_data *d)
{
	if (keycode == 'w')
		d->btns.w = 0;
	else if (keycode == 'a')
		d->btns.a = 0;
	else if (keycode == 's')
		d->btns.s = 0;
	else if (keycode == 'd')
		d->btns.d = 0;
	else if (keycode == KEY_LEFT)
		d->btns.left_arrow = 0;
	else if (keycode == KEY_RIGHT)
		d->btns.right_arrow = 0;
	return (0);
}
