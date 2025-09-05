/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jstuhrin <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/20 15:44:11 by jstuhrin      #+#    #+#                 */
/*   Updated: 2025/08/22 14:43:19 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	focus_in(t_data *d)
{
	d->focus = true;
	return (0);
}

int	focus_out(t_data *d)
{
	d->focus = false;
	return (0);
}

int	mouse_handler(int curr_x, int curr_y, t_data *d)
{
	static int	last_x = 0;
	int			delta_x;

	(void)curr_y;
	if (d->focus == false)
	{
		mlx_mouse_show(d->mlx, d->win);
		return (0);
	}
	mlx_mouse_hide(d->mlx, d->win);
	delta_x = curr_x - WIN_WIDTH / 2;
	d->pl->angle += (double)delta_x * ROTATION_FACTOR_MOUSE;
	d->pl->delta_x = cos(d->pl->angle) * MOVE_SPEED;
	d->pl->delta_y = sin(d->pl->angle) * MOVE_SPEED;
	last_x = curr_x;
	return (0);
}
