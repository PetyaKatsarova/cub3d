/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
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

void	player_control(t_data *d, int keycode)
{
	int dx = 0; // direction
	int dy = 0;

	if (keycode == 'q' || keycode == 65307) // ESC or Q
		exit(0);
	else if (keycode == 'a') // left
	{
		d->player->angle -= 0.1;
		if (d->player->angle < 0) {
			d->player-> angle += 2 * M_PI;
		}
		d->player->delta_x = cos(d->player->angle) * 5;
		d->player->delta_y = sin(d->player->angle) * 5;
	}
	else if (keycode == 'd') // right
	{
		d->player->angle += 0.1;
		if (d->player->angle > 2 * M_PI) {
			d->player-> angle += 2 * M_PI;
		}
		d->player->delta_x = cos(d->player->angle) * 5;
		d->player->delta_y = sin(d->player->angle) * 5;
	}
	else if (keycode == 'w') // up
	{
		d->player->x += d->player->delta_x;
		d->player->y += d->player->delta_y;
	}
	else if (keycode == 's') // down
	{
		d->player->x -= d->player->delta_x;
		d->player->y -= d->player->delta_y;
	}

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
