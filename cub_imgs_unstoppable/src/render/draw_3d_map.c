/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_3d_map.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/30 18:34:37 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/23 17:45:38 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*
** Pythagorean th for right angle triangle: (a² + b² = c²).
** Hypotenuse is the actual ray; a is dist on the x wall to pl and
** y the corresponding.
*/
void	calculate_distances(t_data *d, t_ray_params *params,
			double *hdist, double *vdist)
{
	*hdist = sqrt((params->hx - d->pl->x) * (params->hx - d->pl->x)
			+ (params->hy - d->pl->y) * (params->hy - d->pl->y));
	*vdist = sqrt((params->vx - d->pl->x) * (params->vx - d->pl->x)
			+ (params->vy - d->pl->y) * (params->vy - d->pl->y));
	//if (*hdist <= 1.0 || *hdist > 10000) // dont see for now diff without
	//	*hdist = 10000;
	//if (*vdist <= 1.0 || *vdist > 10000)
	//	*vdist = 10000;
}

/* corrected is fix for fish eye effect */
static void	setup_wall_info(t_wall_info *wall, t_data *d)
{
	float	corrected;

	corrected = wall->distance * cos(wall->ray_angle - d->pl->angle);
	wall->line_h = (TILE_SIZE * WIN_HEIGHT / 2) / corrected;
	wall->wall_top = (WIN_HEIGHT / 2) - (wall->line_h / 2);
	wall->wall_bottom = (WIN_HEIGHT / 2) + (wall->line_h / 2);
}

static t_texture	*set_texture(t_wall_info *wall, t_data *d)
{
	if (wall->hit_vertical)
	{
		if (wall->ray_angle > M_PI / 2 && wall->ray_angle < 3 * M_PI / 2)
			return (&d->west_tex);
		else
			return (&d->east_tex);
	}
	else
	{
		if (wall->ray_angle > M_PI)
			return (&d->north_tex);
		else
			return (&d->south_tex);
	}
}

/*
** The map is split into 64x64 px tiles:
** example: when ray hits a wall at px 150, fmod(150, 64) == 22
** so the ray hit is 22 px into the tile.
*/
static float	set_wall_offset(t_wall_info *wall)
{
	float	offset;

	if (wall->hit_vertical)
	{
		offset = fmod(wall->hit_y, TILE_SIZE);
		if (wall->ray_angle > M_PI / 2 && wall->ray_angle < 3 * M_PI / 2)
			offset = TILE_SIZE - offset;
		return (offset);
	}
	else
	{
		offset = fmod(wall->hit_x, TILE_SIZE);
		if (wall->ray_angle > M_PI)
			offset = TILE_SIZE - offset;
		return (offset);
	}
}

void	draw_3d_wall_slice(t_data *d, int x, t_wall_info *wall)
{
	t_texture	*wall_texture;
	int			y;
	int			tex_x;
	int			tex_y;

	setup_wall_info(wall, d);
	wall_texture = set_texture(wall, d);
	wall->wall_offset = set_wall_offset(wall);
	tex_x = (int)((wall->wall_offset / TILE_SIZE) * wall_texture->width);
	y = 0;
	while (++y < WIN_HEIGHT)
	{
		if (y < wall->wall_top)
			wall->color = d->ceiling;
		else if (y > wall->wall_bottom)
			wall->color = d->floor;
		else
		{
			tex_y = ((y - wall->wall_top) * wall_texture->height)
				/ (wall->wall_bottom - wall->wall_top);
			wall->color = get_texture_pixel(wall_texture, tex_x, tex_y);
		}
		set_px(d, x, y, wall->color);
	}
}
