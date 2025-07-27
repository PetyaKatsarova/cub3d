/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_control.c                                   :+:    :+:            */
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

void	player_control(t_data *d, int keycode)
{
	int dx = 0; // direction
	int dy = 0;

	if (keycode == 'q' || keycode == 65307) // ESC or Q
		exit(0);
	else if (keycode == 'a' && d->player->x >= 1 + TILE_SIZE) // left
		dx = -1;
	else if (keycode == 'd' && d->player->x <= WIDTH - TILE_SIZE - 1) // right
		dx = 1;
	else if (keycode == 'w' && d->player->y >= 1 + TILE_SIZE) // up
		dy = -1;
	else if (keycode == 's' && d->player->y <= HEIGHT - TILE_SIZE - 1) // down
		dy = 1;

	int px = d->player->x / TILE_SIZE;
	int py = d->player->y / TILE_SIZE;
	int nx = px + dx;
	int ny = py + dy;
	if (ny >= 0 && d->map[ny] && nx >= 0 && nx < (int)ft_strlen(d->map[ny])
		&& d->map[ny][nx] == '0')
	{
		d->map[py][px] = '0';
		//d->map[ny][nx] = 'N';
		d->player->x = nx * TILE_SIZE;
		d->player->y = ny * TILE_SIZE;
	}
	printf("Player -> x: %.1f, y: %.1f, angle: %.2f, delta_x: %.2f, delta_y: %.2f\n", d->player->x, d->player->y, d->player->angle, d->player->delta_x, d->player->delta_y);

}
