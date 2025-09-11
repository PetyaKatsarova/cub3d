/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   horizontal_check.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/15 19:50:49 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/09/11 15:43:39 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*
	Divide by TILE_SIZE to find which tile you’re in.
	Floor it to get the top edge of that tile.
	Multiply by TILE_SIZE to get the pixel position.
	Subtract a tiny bit (TILE_SIZE * EPS) to ensure you’re just above
	the line, not exactly on it (avoids bugs).
*/
void	init_h_ray_up(t_data *d, t_ray_params *ray_params)
{
	ray_params->hy = floor(d->pl->y / TILE_SIZE) * TILE_SIZE
		- (TILE_SIZE / 2 * EPS);
	ray_params->hx = (d->pl->y - ray_params->hy)
		* ray_params->h_tan + d->pl->x;
	ray_params->y_offset = -TILE_SIZE;
	ray_params->x_offset = -ray_params->y_offset * ray_params->h_tan;
}

/*
	d->pl->y / TILE_SIZE: Get the tile index (row) where the player is.
	floor(...): Get the integer part (the start of the tile).
	* TILE_SIZE: Convert back to pixel position (top edge of the tile).
	+ TILE_SIZE: Move to the bottom edge of the tile (for rays facing down).
	- EPS: Move just inside the tile to avoid floating-point bugs.
*/
void	init_h_ray_down(t_data *d, t_ray_params *params)
{
	params->hy = floor(d->pl->y / TILE_SIZE) * TILE_SIZE
		+ TILE_SIZE + EPS;
	params->hx = (d->pl->y - params->hy) * params->h_tan + d->pl->x;
	params->y_offset = TILE_SIZE;
	params->x_offset = -params->y_offset * params->h_tan;
}

static bool	is_tiny_intile(t_data *d, t_ray_params *ray_params,
				int map_x, int map_y)
{
	double	x_in_tile;
	double	y_in_tile;

	x_in_tile = fmod(ray_params->hx, TILE_SIZE);
	y_in_tile = fmod(ray_params->hy, TILE_SIZE);
	if (x_in_tile < 0.005 && map_x > 0)
		if (d->map[map_y][map_x - 1] == '1')
			return (true);
	if (x_in_tile > TILE_SIZE - 0.005 && map_x < d->map_cols - 1)
		if (d->map[map_y][map_x + 1] == '1')
			return (true);
	if (y_in_tile < 0.005 && map_y > 0)
		if (d->map[map_y - 1][map_x] == '1')
			return (true);
	if (y_in_tile > TILE_SIZE - 0.005 && map_y < d->map_rows - 1)
		if (d->map[map_y + 1][map_x] == '1')
			return (true);
	return (false);
}

static void	h_check_helper(t_data *d, t_ray_params *ray_params)
{
	int	map_x;
	int	map_y;

	map_x = 0;
	map_y = 0;
	while (ray_params->dof < (d->map_cols + d->map_rows) * 4)
	{
		map_x = (int)(ray_params->hx / TILE_SIZE);
		map_y = (int)(ray_params->hy / TILE_SIZE);
		if (map_x < 0 || map_x >= d->map_cols
			|| map_y < 0 || map_y >= d->map_rows)
			break ;
		if (d->map[map_y][map_x] == '1')
			break ;
		if (is_tiny_intile(d, ray_params, map_x, map_y))
			break ;
		ray_params->hx += ray_params->x_offset;
		ray_params->hy += ray_params->y_offset;
		ray_params->dof++;
	}
}

void	horizontal_check(t_ray *ray, t_data *d, t_ray_params *ray_params)
{
	ray_params->h_tan = -1.0 / tan(ray->angle);
	if (ray->angle > M_PI)
		init_h_ray_up(d, ray_params);
	else if (ray->angle < M_PI)
		init_h_ray_down(d, ray_params);
	else
	{
		ray_params->hx = d->pl->x;
		ray_params->hy = d->pl->y;
		ray_params->dof = d->map_cols;
		return ;
	}
	h_check_helper(d, ray_params);
}
