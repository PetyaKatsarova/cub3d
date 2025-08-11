/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:56:33 by pekatsar          #+#    #+#             */
/*   Updated: 2025/08/11 18:16:44 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* make pl_x,pl_y center fo the player 5px dot diameter dot */
static void	draw_player_dot(t_data *d, int player_x, int player_y, t_minimap_params *params)
{
	int	x;
	int	y;

	y = -2;
	while (y <= 2)
	{
		x = -2;
		while (x <= 2)
		{
			if (player_x + x >= params->offset_x && player_x + x < params->offset_x + MINIMAP_SIZE &&
				player_y + y >= params->offset_y && player_y + y < params->offset_y + MINIMAP_SIZE)
				set_px(d, player_x + x, player_y + y, LIME_YELLOW);
			x++;
		}
		y++;
	}
}

static void	draw_player_direction(t_data *d, int player_x, int player_y)
{
	t_line_info	line;

	line.x0 = player_x;
	line.y0 = player_y;
	line.x1 = player_x + (cos(d->pl->angle) * VECTOR_LEN);
	line.y1 = player_y + (sin(d->pl->angle) * VECTOR_LEN);
	line.color = PURPLE_RAY;
	draw_line(d, &line);
}

static void another_helper(t_ray_params ray_params, t_data *d, float *hit_x, float *hit_y)
{
	float hdist;
	float vdist;
	
	hdist = sqrt((ray_params.hx - d->pl->x) * (ray_params.hx - d->pl->x) +
                 (ray_params.hy - d->pl->y) * (ray_params.hy - d->pl->y));
    vdist = sqrt((ray_params.vx - d->pl->x) * (ray_params.vx - d->pl->x) +
                 (ray_params.vy - d->pl->y) * (ray_params.vy - d->pl->y));

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

static void	draw_single_ray(t_data *d, float ray_angle, t_minimap_params *params, int player_x, int player_y)
{
    t_ray			ray;
    t_ray_params	ray_params;
    float			hdist, vdist;
    float			hit_x, hit_y;
    int				ray_end_x, ray_end_y;
    t_line_info		line;

    ray.angle = ray_angle;
	init_ray_params(ray_params);
    horizontal_check(&ray, d, &ray_params);
    vertical_check(&ray, d, &ray_params);
	another_helper(ray_params, d, &hit_x, &hit_y);
    ray_end_x = params->offset_x + (hit_x * params->scale);
    ray_end_y = params->offset_y + (hit_y * params->scale);
    if (ray_end_x >= params->offset_x && ray_end_x < params->offset_x + MINIMAP_SIZE &&
        ray_end_y >= params->offset_y && ray_end_y < params->offset_y + MINIMAP_SIZE)
    {
        line.x0 = player_x;
        line.y0 = player_y;
        line.x1 = ray_end_x;
        line.y1 = ray_end_y;
        line.color = PL_COLOR;
        draw_line(d, &line);
    }
}

static void	draw_minimap_rays(t_data *d, t_minimap_params *params, int player_x, int player_y)
{
	float	ray_angle;
	int		i;

	ray_angle = normalize_angle(d->pl->angle - (d->pl->fov / 2));
	i = 0;
	while (i < RAYS_NUM)
	{
		draw_single_ray(d, ray_angle, params, player_x, player_y);
		ray_angle = normalize_angle(ray_angle + (d->pl->fov / RAYS_NUM));
		i++;
	}
}

void	draw_minimap(t_data *d)
{
	t_minimap_params	params;
	int					player_x;
	int					player_y;

	params.offset_x = WIN_WIDTH - MINIMAP_SIZE - 10;
	params.offset_y = 10;
	params.scale = (float)MINIMAP_SIZE / (d->map_cols * TILE_SIZE);
	draw_minimap_background(d, params.offset_x, params.offset_y, &params);
	draw_minimap_walls(d, params.offset_x, params.offset_y, params.scale);
	player_x = params.offset_x + (d->pl->x * params.scale);
	player_y = params.offset_y + (d->pl->y * params.scale);
	draw_player_dot(d, player_x, player_y, &params);
	draw_player_direction(d, player_x, player_y);
	draw_minimap_rays(d, &params, player_x, player_y);
}
