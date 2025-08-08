/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/06 16:56:33 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/08 16:05:19 by pekatsar      ########   odam.nl         */
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
/* could be refactored, still neat enough, t_line_info struct is needed to pass coding norms(max 4 args in func draw_line) */
static void	draw_player_direction(t_data *d, int player_x, int player_y)
{
	t_line_info	line;

	line.x0 = player_x;
	line.y0 = player_y;
	line.x1 = player_x + (cos(d->pl->angle) * 20);
	line.y1 = player_y + (sin(d->pl->angle) * 20);
	line.color = PURPLE_RAY;
	draw_line(d, &line);
}

static void	draw_single_ray(t_data *d, float ray_angle, t_minimap_params *params, int player_x, int player_y)
{
	t_ray		ray;
	float		hx, hy, vx, vy;
	float		hdist, vdist;
	float		hit_x, hit_y;
	int			ray_end_x, ray_end_y;
	t_line_info	line;

	ray.angle = ray_angle;
	horizontal_check(&ray, d, &hx, &hy);
	vertical_check(&ray, d, &vx, &vy);
	hdist = sqrt((hx - d->pl->x) * (hx - d->pl->x) + (hy - d->pl->y) * (hy - d->pl->y));
	vdist = sqrt((vx - d->pl->x) * (vx - d->pl->x) + (vy - d->pl->y) * (vy - d->pl->y));
	if (hdist < vdist)
	{
		hit_x = hx;
		hit_y = hy;
	}
	else
	{
		hit_x = vx;
		hit_y = vy;
	}
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
	draw_minimap_background(d, params.offset_x, params.offset_y);
	draw_minimap_walls(d, params.offset_x, params.offset_y, params.scale);
	player_x = params.offset_x + (d->pl->x * params.scale);
	player_y = params.offset_y + (d->pl->y * params.scale);
	draw_player_dot(d, player_x, player_y, &params);
	draw_player_direction(d, player_x, player_y);
	draw_minimap_rays(d, &params, player_x, player_y);
}
