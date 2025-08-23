/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   horizontal_check.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/15 19:50:49 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/23 11:30:01 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	init_h_ray_up(t_data *d, t_ray_params *ray_params)
{
	ray_params->hy = floor(d->pl->y / TILE_SIZE) * TILE_SIZE - (TILE_SIZE * 0.001);
	ray_params->hx = (d->pl->y - ray_params->hy)
		* ray_params->h_tan + d->pl->x;
	ray_params->yo = -TILE_SIZE;
	ray_params->xo = -ray_params->yo * ray_params->h_tan;
}

void	init_h_ray_down(t_data *d, t_ray_params *params)
{
	params->hy = floor(d->pl->y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	params->hx = (d->pl->y - params->hy) * params->h_tan + d->pl->x;
	params->yo = TILE_SIZE;
	params->xo = -params->yo * params->h_tan;
}

static void	h_check_helper(t_data *d, t_ray_params *ray_params)
{
	int	map_x;
	int	map_y;

	map_x = 0;
	map_y = 0;
	ray_params->dof = 0;
	while (ray_params->dof < d->map_rows)
	{
		map_x = (int)(ray_params->hx / TILE_SIZE);
		map_y = (int)(ray_params->hy / TILE_SIZE);
		if (map_x >= 0 && map_x < d->map_cols
			&& map_y >= 0 && map_y < d->map_rows
			&& d->map[map_y][map_x] == '1')
			break ;
		else
		{
			ray_params->hx += ray_params->xo;
			ray_params->hy += ray_params->yo;
			ray_params->dof++;
		}
	}
}

void	horizontal_check(t_ray *ray, t_data *d, t_ray_params *ray_params)
{
	ray_params->h_tan = -1.0 / tan(ray->angle);
	ray_params->dof = 0;
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
