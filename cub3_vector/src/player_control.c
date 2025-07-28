/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:22:20 by pekatsar          #+#    #+#             */
/*   Updated: 2025/07/27 20:27:45 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int ft_strlen(const char *s)
{
	int len = 0;
	while (s[len])
		len++;
	return len;
}	
// float px, py, pdx, pdy, pa
void	pl_control(t_data *d, int keycode)
{
	int dx = 0; // direction
	int dy = 0;

	if (keycode == 'q' || keycode == 65307) // ESC or Q
		exit(0);
	else if (keycode == 'a') // rotate left
	{
		d->pl->angle -= 0.1;
		if (d->pl->angle < 0)
			d->pl-> angle += 2 * M_PI;

		d->pl->delta_x = cos(d->pl->angle) * 5;
		d->pl->delta_y = sin(d->pl->angle) * 5;
	}
	else if (keycode == 'd') // rotate right
	{
		d->pl->angle += 0.1;
		if (d->pl->angle > 2 * M_PI) {
			d->pl-> angle -= 2 * M_PI;
		}
		d->pl->delta_x = cos(d->pl->angle) * 5;
		d->pl->delta_y = sin(d->pl->angle) * 5;
	}
	else if (keycode == 'w') // move fwd/towards
	{
		d->pl->x += d->pl->delta_x;
		d->pl->y += d->pl->delta_y;
	}
	else if (keycode == 's') // move away/backwards
	{
		d->pl->x -= d->pl->delta_x;
		d->pl->y -= d->pl->delta_y;
	}
	printf("pl -> x: %.1f, y: %.1f, angle: %.2f, delta_x: %.2f, delta_y: %.2f\n", d->pl->x, d->pl->y, d->pl->angle, d->pl->delta_x, d->pl->delta_y);

}
