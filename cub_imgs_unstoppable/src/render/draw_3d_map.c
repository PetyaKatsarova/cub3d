/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_3d_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/30 18:34:37 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/01 14:58:30 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	calculate_distances(t_data *d, t_ray_params *params, float *hdist, float *vdist)
{
    *hdist = sqrt((params->hx - d->pl->x) * (params->hx - d->pl->x) 
        + (params->hy - d->pl->y) * (params->hy - d->pl->y));
    *vdist = sqrt((params->vx - d->pl->x) * (params->vx - d->pl->x) 
        + (params->vy - d->pl->y) * (params->vy - d->pl->y));
    
    // Safety checks for invalid distances
    if (*hdist <= 1.0 || *hdist > 10000)
        *hdist = 10000;
    if (*vdist <= 1.0 || *vdist > 10000)
        *vdist = 10000;
}

static void setup_wall_info(t_wall_info *wall, t_data *d)
{
    wall->distance = wall->distance * cos(wall->ray_angle - d->pl->angle);
    wall->line_h = (TILE_SIZE * WIN_HEIGHT / 2) / wall->distance;
    wall->wall_top = (WIN_HEIGHT / 2) - (wall->line_h / 2);
    wall->wall_bottom = (WIN_HEIGHT / 2) + (wall->line_h / 2);
}

static t_texture *set_texture(t_wall_info *wall, t_data *d)
{
    if (wall->hit_vertical)
    {
        if (wall->ray_angle > M_PI/2 && wall->ray_angle < 3*M_PI/2)
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

static float set_wall_offset(t_wall_info *wall)
{
    if (wall->hit_vertical)
        return fmod(wall->hit_y, TILE_SIZE);
    else
        return fmod(wall->hit_x, TILE_SIZE);
}

void draw_3d_wall_slice(t_data *d, int x, t_wall_info *wall)
{
    t_texture	*wall_texture;
    int			y;
    int			tex_x;
    int			tex_y;

    setup_wall_info(wall, d);
    wall_texture = set_texture(wall, d);
    y = 0;
    while (y < WIN_HEIGHT)
    {
        if (y < wall->wall_top)
            wall->color = CEILING_COLOR;
        else if (y > wall->wall_bottom)
            wall->color = FLOOR_COLOR;
        else
        {
            wall->wall_offset = set_wall_offset(wall);
            tex_x = (int)((wall->wall_offset / TILE_SIZE) * wall_texture->width);
            tex_y = ((y - wall->wall_top) * wall_texture->height) / (wall->wall_bottom - wall->wall_top);
            wall->color = get_texture_pixel(wall_texture, tex_x, tex_y);
        }
        set_px(d, x, y, wall->color);
        y++;
    }
}
