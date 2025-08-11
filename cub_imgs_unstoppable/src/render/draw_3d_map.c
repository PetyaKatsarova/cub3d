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

void set_px(t_data *d, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		uint32_t *pixels = (uint32_t *)d->addr;
		int index = y * (d->line_length / 4) + x;
		pixels[index] = color;
	}
}

static void	calculate_distances(t_data *d, t_ray_params *params, float *hdist, float *vdist)
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

static void draw_3d_wall_slice(t_data *d, int x, t_wall_info *wall)
{
    float		lineH;
    int			wall_top;
    int			wall_bottom;
    t_texture	*wall_texture;
    int			y;
    uint32_t	color;
    float		wall_offset;
    int			tex_x;
    int			tex_y;

    // fish eye correction
    wall->distance = wall->distance * cos(wall->ray_angle - d->pl->angle);
    lineH = (TILE_SIZE * WIN_HEIGHT / 2) / wall->distance;
    wall_top = (WIN_HEIGHT / 2) - (lineH / 2);
    wall_bottom = (WIN_HEIGHT / 2) + (lineH / 2);
    if (wall->hit_vertical)
    {
        if (wall->ray_angle > M_PI/2 && wall->ray_angle < 3*M_PI/2)
            wall_texture = &d->west_tex;
        else
            wall_texture = &d->east_tex;
    }
    else
    {
        if (wall->ray_angle > M_PI)
            wall_texture = &d->north_tex;
        else
            wall_texture = &d->south_tex;
    }
    y = 0;
    while (y < WIN_HEIGHT)
    {
        if (y < wall_top)
            color = CEILING_COLOR;
        else if (y > wall_bottom)
            color = FLOOR_COLOR;
        else
        {
            if (wall->hit_vertical)
                wall_offset = fmod(wall->hit_y, TILE_SIZE);
            else
                wall_offset = fmod(wall->hit_x, TILE_SIZE);
            tex_x = (int)((wall_offset / TILE_SIZE) * wall_texture->width);
            tex_y = ((y - wall_top) * wall_texture->height) / (wall_bottom - wall_top);
            color = get_texture_pixel(wall_texture, tex_x, tex_y);
        }
        set_px(d, x, y, color);
        y++;
    }
}

static void	draw_3d_map(t_data *d, t_ray *ray)
{
    t_ray_params	params;
    float			hdist, vdist;
    t_wall_info		wall;
    int				x;

    ray->angle = d->pl->angle - (30.0 * DEG_RAD);
    if (ray->angle < 0)
        ray->angle += 2 * M_PI;
    else if (ray->angle > 2 * M_PI)
        ray->angle -= 2 * M_PI;
    
    x = 0;
    while (x < WIN_WIDTH)
    {
        init_ray_params(params);
        horizontal_check(ray, d, &params);
        vertical_check(ray, d, &params);
        calculate_distances(d, &params, &hdist, &vdist);
        
        if (hdist < vdist)
        {
            wall.distance = hdist;
            wall.hit_x = params.hx;
            wall.hit_y = params.hy;
            wall.hit_vertical = 0;
        }
        else
        {
            wall.distance = vdist;
            wall.hit_x = params.vx;
            wall.hit_y = params.vy;
            wall.hit_vertical = 1;
        }
        wall.raw_dist = wall.distance;
        wall.ray_angle = ray->angle;
        draw_3d_wall_slice(d, x, &wall);
        
        ray->angle += (60.0 * DEG_RAD) / WIN_WIDTH;
        if (ray->angle < 0)
            ray->angle += 2 * M_PI;
        if (ray->angle > 2 * M_PI)
            ray->angle -= 2 * M_PI;
        x++;
    }
}

int render_frame(t_data *d)
{
    t_ray ray;

    ray.angle = d->pl->angle;
    pl_control(d);
    draw_3d_map(d, &ray);
    draw_minimap(d);
    mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);   
    return (0);
}