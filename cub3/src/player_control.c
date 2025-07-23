/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_control.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 15:22:20 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/07/23 17:05:14 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int sft_trlen(char *str)
{
	int len = 0;
	while (str[len] != '\0')
		len++;
	return len;
}

void	player_control(t_data *d, int keycode)
{
	int dx = 0; // direction
	int dy = 0;

	if (keycode == 65307) // ESC
		exit(0);
	else if (keycode == 65361 && d->player_x >= 1 + TILE_SIZE) // left
		dx = -1;
	else if (keycode == 65363 && d->player_x <= WIDTH - TILE_SIZE - 1) // right
		dx = 1;
	else if (keycode == 65362 && d->player_y >= 1 + TILE_SIZE) // up
		dy = -1;
	else if (keycode == 65364 && d->player_y <= HEIGHT - TILE_SIZE - 1) // down
		dy = 1;

	int px = d->player_x / TILE_SIZE;
	int py = d->player_y / TILE_SIZE;
	int nx = px + dx;
	int ny = py + dy;
	if (ny >= 0 && d->map[ny] && nx >= 0 && nx < (int)sft_trlen(d->map[ny])
		&& d->map[ny][nx] == '0')
	{
		d->map[py][px] = '0';
		d->map[ny][nx] = 'N';
		d->player_x = nx * TILE_SIZE;
		d->player_y = ny * TILE_SIZE;
	}
}