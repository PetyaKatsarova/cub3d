/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap3.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/15 19:49:13 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/09/11 18:57:17 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*
	Pythagorean th: a² + b² = hypothenose²
	hypothenose = sqrt(a² + b²)
*/
static void	set_hit_xy(t_ray_params ray_params, t_data *d,
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

/*
	Casts a ray from the player, finds where it hits a wall, and converts
	that hit position to minimap coordinates.
*/
static void	compute_ray_end(t_data *d, float ray_angle, int *out_x, int *out_y)
{
	t_ray			ray;
	t_ray_params	ray_params;
	float			hit_x;
	float			hit_y;

	ray.angle = ray_angle;
	init_ray_params(&ray_params);
	horizontal_check(&ray, d, &ray_params);
	vertical_check(&ray, d, &ray_params);
	set_hit_xy(ray_params, d, &hit_x, &hit_y);
	*out_x = d->params->offset_x + (int)(hit_x * d->params->scale);
	*out_y = d->params->offset_y + (int)(hit_y * d->params->scale);
}

void	draw_single_ray(t_data *d, float ray_angle, int player_x, int player_y)
{
	int				ray_end_x;
	int				ray_end_y;
	t_line_info		line;
	t_line_math		helper;

	compute_ray_end(d, ray_angle, &ray_end_x, &ray_end_y);
	if (ray_end_x >= d->params->offset_x
		&& ray_end_x < d->params->offset_x + MINIMAP_SIZE
		&& ray_end_y >= d->params->offset_y
		&& ray_end_y < d->params->offset_y + MINIMAP_SIZE)
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
	d->params = params;
	i = 0;
	while (i < RAYS_NUM)
	{
		draw_single_ray(d, ray_angle, player_x, player_y);
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
	if (d->map_rows > d->map_cols)
		params.scale = (float)MINIMAP_SIZE / (d->map_rows * TILE_SIZE);
	draw_minimap_background(d, params.offset_x, params.offset_y, &params);
	draw_minimap_walls(d, params.offset_x, params.offset_y, params.scale);
	player_x = params.offset_x + (d->pl->x * params.scale);
	player_y = params.offset_y + (d->pl->y * params.scale);
	draw_player_dot(d, player_x, player_y, &params);
	draw_player_direction(d, player_x, player_y);
	draw_minimap_rays(d, &params, player_x, player_y);
}
