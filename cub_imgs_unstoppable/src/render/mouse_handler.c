/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   mouse_handler.c                                        :+:    :+:        */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/20 15:44:11 by jstuhrin       #+#    #+#                */
/*   Updated: 2025/08/21 11:47:13 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	mouse_handler(int curr_x, int curr_y, t_data *d)
{
	static int	last_x = 0;
	int			delta_x;

	mlx_mouse_hide(d->mlx, d->win);
	delta_x = curr_x - last_x;
	if (delta_x < -1)
	{
		d->pl->angle -= 0.02;
		if (d->pl->angle < 0)
			d->pl->angle += 2 * M_PI;
	}
	if (delta_x > 1)
	{
		d->pl->angle += 0.02;
		if (d->pl->angle > 2 * M_PI)
			d->pl->angle -= 2 * M_PI;
	}
	d->pl->delta_x = cos(d->pl->angle) * 5;
	d->pl->delta_y = sin(d->pl->angle) * 5;
	last_x = curr_x;
	return (0);
}
