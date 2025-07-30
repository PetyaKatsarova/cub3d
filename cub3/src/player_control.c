/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pl_control.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 15:22:20 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/07/25 17:34:36 by pekatsar      ########   odam.nl         */
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

void	pl_control(t_data *d, int keycode)
{
	int dx = 0; // direction
	int dy = 0;

	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_LEFT && d->pl->x >= 1 + TILE_SIZE)
		dx = -1;
	else if (keycode == KEY_RIGHT && d->pl->x <= WIDTH - TILE_SIZE - 1)
		dx = 1;
	else if (keycode == KEY_UP && d->pl->y >= 1 + TILE_SIZE)
		dy = -1;
	else if (keycode == KEY_DOWN && d->pl->y <= HEIGHT - TILE_SIZE - 1)
		dy = 1;

	int px = d->pl->x / TILE_SIZE;
	int py = d->pl->y / TILE_SIZE;
	int nx = px + dx;
	int ny = py + dy;
	if (ny >= 0 && d->map[ny] && nx >= 0 && nx < (int)ft_strlen(d->map[ny])
		&& d->map[ny][nx] == '0')
	{
		d->map[py][px] = '0';
		//d->map[ny][nx] = 'N';
		d->pl->x = nx * TILE_SIZE;
		d->pl->y = ny * TILE_SIZE;
	}
	printf("pl -> x: %.1f, y: %.1f, angle: %.2f, delta_x: %.2f, delta_y: %.2f\n", d->pl->x, d->pl->y, d->pl->angle, d->pl->delta_x, d->pl->delta_y);

}
