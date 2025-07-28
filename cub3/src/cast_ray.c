/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:36:45 by pekatsar          #+#    #+#             */
/*   Updated: 2025/07/27 20:45:36 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
	draw red dot at hit of wall
*/
static void set_px (t_data *d, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		((int *)d->addr)[y * (d->line_length / 4) + x] = color;
	}
}

/**
 * For every vertical stripe on screen (or every N pixels), cast a ray from the pl’s position.
	Step along that ray direction until it hits a wall.
	Draw a vertical line to simulate the 3D wall.
 */
void cast_rays(t_data *d)
{
	int ray;
	double ray_angle;

	ray_angle = d->pl->angle - (M_PI / 6); // 30 degrees to the left
	ray = 0;
	if (ray_angle < 0)
		ray_angle += 2 * M_PI; // wrap around
	while (ray < WIDTH)
	{
		double ray_x = d->pl->x;
		double ray_y = d->pl->y;
		double ray_dx = cos(ray_angle);
		double ray_dy = sin(ray_angle);
		while (1)
		{
			int map_x = (int)(ray_x / TILE_SIZE);
			int map_y = (int)(ray_y / TILE_SIZE);
			if (map_y < 0 || map_y >= HEIGHT / TILE_SIZE ||
				map_x < 0 || map_x >= WIDTH / TILE_SIZE ||
				d->map[map_y][map_x] == '1') // hit a wall
				{
					printf("ray hit at tile: %d,%d (ray: %d)\n", map_x, map_y, ray);
					break;
				}
			ray_x += ray_dx;
			ray_y += ray_dy;
		}
		// draw vertical ray line in 2D minimap (optional)
		set_px(d, ray_x, ray_y, 0xFF0000);
		ray_angle += (M_PI / 3) / WIDTH; // 60 degrees total, divided by screen width
		if (ray_angle >= 2 * M_PI)
			ray_angle -= 2 * M_PI; // wrap around
		ray++;
	}
}

//set_pixel(d, ray_x, ray_y, 0xFF0000);
//draw_maze(d);
//cast_rays(d); // <---