/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap3.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/15 19:49:13 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/22 14:15:24 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	another_helper(t_ray_params ray_params, t_data *d,
				float *hit_x, float *hit_y)
{
	float	hdist;
	float	vdist;

	hdist = sqrt((ray_params.hx - d->pl->x)
			* (ray_params.hx - d->pl->x)
			+ (ray_params.hy - d->pl->y)
			* (ray_params.hy - d->pl->y));
	vdist = sqrt((ray_params.vx - d->pl->x)
			* (ray_params.vx - d->pl->x)
			+ (ray_params.vy - d->pl->y)
			* (ray_params.vy - d->pl->y));
	if (hdist < vdist)
	{
		*hit_x = ray_params.hx;
		*hit_y = ray_params.hy;
	}
	else
	{
		*hit_x = ray_params.vx;
		*hit_y = ray_params.vy;
	}
}

void	draw_single_ray(t_data *d, float ray_angle,
			t_minimap_params *params, int player_x, int player_y)
{
	t_ray			ray;
	t_ray_params	ray_params;
	float			hit_x;
	float			hit_y;
	int				ray_end_x;
	int				ray_end_y;
	t_line_info		line;
	t_helper		helper;

	ray.angle = ray_angle;
	init_ray_params(&ray_params);
	horizontal_check(&ray, d, &ray_params);
	vertical_check(&ray, d, &ray_params);
	another_helper(ray_params, d, &hit_x, &hit_y);
	ray_end_x = params->offset_x + (hit_x * params->scale);
	ray_end_y = params->offset_y + (hit_y * params->scale);
	if (ray_end_x >= params->offset_x
		&& ray_end_x < params->offset_x + MINIMAP_SIZE
		&& ray_end_y >= params->offset_y
		&& ray_end_y < params->offset_y + MINIMAP_SIZE)
	{
		line.x0 = player_x;
		line.y0 = player_y;
		line.x1 = ray_end_x;
		line.y1 = ray_end_y;
		line.color = PL_COLOR;
		draw_line(d, &line, &helper);
	}
}

static void	draw_minimap_rays(t_data *d, t_minimap_params *params,
				int player_x, int player_y)
{
	float	ray_angle;
	int		i;

	ray_angle = normalize_angle(d->pl->angle - (d->pl->fov / 2));
	i = 0;
	while (i < RAYS_NUM)
	{
		draw_single_ray(d, ray_angle, params, player_x, player_y);
		ray_angle = normalize_angle(ray_angle
				+ (d->pl->fov / RAYS_NUM));
		i++;
	}
}

void	draw_minimap(t_data *d)
{
	t_minimap_params	params;
	int					player_x;
	int					player_y;

	params.offset_x = WIN_WIDTH - MINIMAP_SIZE;
	params.offset_y = 0;
	params.scale = (float)MINIMAP_SIZE / (d->map_cols * TILE_SIZE);
	draw_minimap_background(d, params.offset_x, params.offset_y, &params);
	draw_minimap_walls(d, params.offset_x, params.offset_y, params.scale);
	player_x = params.offset_x + (d->pl->x * params.scale);
	player_y = params.offset_y + (d->pl->y * params.scale);
	draw_player_dot(d, player_x, player_y, &params);
	draw_player_direction(d, player_x, player_y);
	draw_minimap_rays(d, &params, player_x, player_y);
}
