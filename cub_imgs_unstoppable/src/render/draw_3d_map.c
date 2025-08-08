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

void horizontal_check(t_ray *ray, t_data *d, float *hx, float *hy)
{
    float aTan = -1/tan(ray->angle);
    int dof = 0;
    float xo, yo; // STEP_SIZE offsets
    
    if (ray->angle > M_PI) { // looking up
        *hy = (((int)d->pl->y>>6)<<6) - 0.0001;
        *hx = (d->pl->y - *hy) * aTan + d->pl->x;
        yo = -TILE_SIZE;
        xo = -yo * aTan;
    } // OR ADD ELSE: ODNT SEE DIFF??
    if (ray->angle < M_PI) { // looking down
        *hy = (((int)d->pl->y>>6)<<6) + TILE_SIZE;
        *hx = (d->pl->y - *hy) * aTan + d->pl->x;
        yo = TILE_SIZE;
        xo = -yo * aTan;
    }
    if (ray->angle == 0 || ray->angle == M_PI ){ // looking straight left/right
        *hx = d->pl->x;
        *hy = d->pl->y;
        dof = d->map_cols; // skip loop
    }
    
    // STEP_SIZE through horizontal grid lines
    while (dof < d->map_cols)
    {
        int map_x = (int)(*hx / TILE_SIZE); 
        int map_y = (int)(*hy / TILE_SIZE);
		//int map_x = (int)ray->x>>6;
		//int map_y = (int)ray->y>>6;
        
        if (map_x >= 0 && map_x < d->map_cols && map_y >= 0 && map_y < d->map_rows && 
            d->map[map_y][map_x] == '1')
        {
            break; // hit wall - STOP HERE
        }
        else {
            *hx += xo; // STEP_SIZE to next grid line
            *hy += yo;
            dof++;
        }
    }
}

void vertical_check(t_ray *ray, t_data *d, float *vx, float *vy)
{
    float nTan = -tan(ray->angle);
    int dof = 0;
    float xo, yo; // STEP_SIZE offsets
    
    if (ray->angle > M_PI/2 && ray->angle < 3*M_PI/2) { // looking left
        *vx = (((int)d->pl->x>>6)<<6) - 0.0001;
        *vy = (d->pl->x - *vx) * nTan + d->pl->y;
        xo = -TILE_SIZE;
        yo = -xo * nTan;
    }
    else if (ray->angle < M_PI/2 || ray->angle > 3*M_PI/2) { // looking right
        *vx = (((int)d->pl->x>>6)<<6) + TILE_SIZE;
        *vy = (d->pl->x - *vx) * nTan + d->pl->y;
        xo = TILE_SIZE;
        yo = -xo * nTan;
    }
    else { // looking straight up/down
        *vx = d->pl->x;
        *vy = d->pl->y;
        dof = d->map_cols; // skip loop
    }
    
    // STEP_SIZE through vertical grid lines
    while (dof < d->map_cols)
    {
        int map_x = (int)floor(*vx / TILE_SIZE);
        int map_y = (int)floor(*vy / TILE_SIZE);
        
        if (map_x >= 0 && map_x < d->map_cols && map_y >= 0 && map_y < d->map_rows && 
            d->map[map_y][map_x] == '1')
        {
            break; // hit wall - STOP HERE
        }
        else {
            *vx += xo; // STEP_SIZE to next grid line
            *vy += yo;
            dof++;
        }
    }
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

	// fish eye
    wall->distance = wall->distance * cos(wall->ray_angle - d->pl->angle);
    lineH = (TILE_SIZE * WIN_HEIGHT / 2) / wall->distance;
    wall_top = (WIN_HEIGHT / 2) - (lineH / 2);
    wall_bottom = (WIN_HEIGHT / 2) + (lineH / 2);
    if (wall_top < 0)
        wall_top = 0;
    if (wall_bottom >= WIN_HEIGHT)
        wall_bottom = WIN_HEIGHT - 1;
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

static void draw_3d_map(t_data *d, t_ray *ray) 
{
	ray->angle = d->pl->angle - (30.0 * DEG_RAD);
    
    if (ray->angle < 0)
        ray->angle += 2 * M_PI;
    else if (ray->angle > 2 * M_PI)
        ray->angle -= 2 * M_PI;

    for (int x = 0; x < WIN_WIDTH; x++)
    {
        float hx, hy;
        float vx, vy;
        
        horizontal_check(ray, d, &hx, &hy);
        vertical_check(ray, d, &vx, &vy);
        
        float hdist = sqrt((hx - d->pl->x) * (hx - d->pl->x) + (hy - d->pl->y) * (hy - d->pl->y));
        float vdist = sqrt((vx - d->pl->x) * (vx - d->pl->x) + (vy - d->pl->y) * (vy - d->pl->y));
        
        float distance;
        int hit_vertical;
        
        if (hdist < vdist)
        {
            ray->x = hx;
            ray->y = hy;
            distance = hdist;
            hit_vertical = 0;
        }
        else
        {
            ray->x = vx;
            ray->y = vy;
            distance = vdist;
            hit_vertical = 1; 
        }        
        
        // Replace the function call with:
		t_wall_info wall;
		wall.distance = distance;
		wall.raw_dist = distance;
		wall.ray_angle = ray->angle;
		wall.hit_vertical = hit_vertical;
		wall.hit_x = ray->x;
		wall.hit_y = ray->y;
		draw_3d_wall_slice(d, x, &wall);

        ray->angle += (60.0 * DEG_RAD) / WIN_WIDTH;
        
        if (ray->angle < 0)
            ray->angle += 2 * M_PI;
        if (ray->angle > 2 * M_PI)
            ray->angle -= 2 * M_PI;
    }
}

int render_frame(t_data *d)
{
	pl_control(d);
    //// Clear screen
    //for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
    //    ((uint32_t*)d->addr)[i] = BLACK;

    t_ray ray;
    ray.angle = d->pl->angle;
    draw_3d_map(d, &ray);
    draw_minimap(d);
    mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);   
    return (0);
}