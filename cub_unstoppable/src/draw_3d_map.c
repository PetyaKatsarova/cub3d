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

#include "../include/cub3D.h"

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
    float xo, yo; // step offsets
    
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
        dof = COLS; // skip loop
    }
    
    // Step through horizontal grid lines
    while (dof < COLS)
    {
        int map_x = (int)(*hx / TILE_SIZE); 
        int map_y = (int)(*hy / TILE_SIZE);
		//int map_x = (int)ray->x>>6;
		//int map_y = (int)ray->y>>6;
        
        if (map_x >= 0 && map_x < COLS && map_y >= 0 && map_y < ROWS && 
            d->map[map_y][map_x] == '1')
        {
            break; // hit wall - STOP HERE
        }
        else {
            *hx += xo; // step to next grid line
            *hy += yo;
            dof++;
        }
    }
}

void vertical_check(t_ray *ray, t_data *d, float *vx, float *vy)
{
    float nTan = -tan(ray->angle);
    int dof = 0;
    float xo, yo; // step offsets
    
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
        dof = COLS; // skip loop
    }
    
    // Step through vertical grid lines
    while (dof < COLS)
    {
        int map_x = (int)floor(*vx / TILE_SIZE);
        int map_y = (int)floor(*vy / TILE_SIZE);
        
        if (map_x >= 0 && map_x < COLS && map_y >= 0 && map_y < ROWS && 
            d->map[map_y][map_x] == '1')
        {
            break; // hit wall - STOP HERE
        }
        else {
            *vx += xo; // step to next grid line
            *vy += yo;
            dof++;
        }
    }
}

static void draw_3d_wall_slice(t_data *d, int x, float distance, float ray_angle, int hit_vertical)
{
    // Fix fisheye distortion
    distance = distance * cos(ray_angle - d->pl->angle);
    
    // wall height on screen
    float lineH = (TILE_SIZE * WIN_HEIGHT / 2) / distance;
    
    // wall boundaries
    int wall_top = (WIN_HEIGHT / 2) - (lineH / 2);
    int wall_bottom = (WIN_HEIGHT / 2) + (lineH / 2);
    
    // Clamp(constrain) to screen bounds:
    if (wall_top < 0) wall_top = 0;
    if (wall_bottom >= WIN_HEIGHT) wall_bottom = WIN_HEIGHT - 1;
    
    // Get wall color based on direction
    uint32_t wall_color;
    if (hit_vertical) {
        // East/West walls
        if (ray_angle > M_PI/2 && ray_angle < 3*M_PI/2)
            wall_color = WEST_COLOR; 
        else
            wall_color = EAST_COLOR; 
    }
    else {
        // North/South walls  
        if (ray_angle > M_PI)
            wall_color = NORTH_COLOR;
        else
            wall_color = SOUTH_COLOR;
    }
   
    // Draw vertical line (ceiling, wall, floor)
    for (int y = 0; y < WIN_HEIGHT; y++)
    {
        uint32_t color;
        
        if (y < wall_top)
            color = CEILING_COLOR;
        else if (y > wall_bottom)
            color = FLOOR_COLOR;  
        else
            color = wall_color;       // Directional wall color
            
        set_px(d, x, y, color);
    }
}

// static void draw_3d_wall_slice(t_data *d, int x, float distance, float hit_x, float hit_y, float ray_angle, int hit_vertical)
// {
//     // Fix fisheye distortion
//     distance = distance * cos(ray_angle - d->pl->angle);
    
//     // wall height on screen
//     float lineH = (TILE_SIZE * WIN_HEIGHT / 2) / distance;
    
//     // wall boundaries
//     int wall_top = (WIN_HEIGHT / 2) - (lineH / 2);
//     int wall_bottom = (WIN_HEIGHT / 2) + (lineH / 2);
    
//     // Clamp(constrain) to screen bounds:
//     if (wall_top < 0) wall_top = 0;
//     if (wall_bottom >= WIN_HEIGHT) wall_bottom = WIN_HEIGHT - 1;
   
//     t_texture *tex;
//     if (hit_vertical) {
//         if (ray_angle > M_PI/2 && ray_angle < 3*M_PI/2)
//             tex = &d->west_tex;
//         else
//             tex = &d->east_tex;
//     } else {
//         if (ray_angle > M_PI)
//             tex = &d->north_tex;
//         else
//             tex = &d->south_tex;
//     }

//     int tex_x;
//     if (hit_vertical) {
//         tex_x = (int)(hit_y) % TILE_SIZE;
//     } else {
//         tex_x = (int)(hit_x) % TILE_SIZE;
//     }
//     tex_x = (tex_x * tex->width) / TILE_SIZE; // Scale to texture width
    
//     // Draw the wall column
//     for (int y = 0; y < WIN_HEIGHT; y++)
//     {
//         uint32_t color;
        
//         if (y < wall_top)
//             color = CEILING_COLOR;
//         else if (y > wall_bottom)
//             color = FLOOR_COLOR;
//         else {
//             // Calculate which row of the texture to use
//             int tex_y = ((y - wall_top) * tex->height) / (wall_bottom - wall_top);
//             color = get_texture_pixel(tex, tex_x, tex_y);
//         }
        
//         set_px(d, x, y, color);
//     }
// }

static void draw_3d_map(t_data *d, t_ray *ray) 
{
    //ray->angle = d->pl->angle - (30.0 * DEG_RAD);
	ray->angle = d->pl->angle - (30.0 * DEG_RAD);
    
    if (ray->angle < 0)
        ray->angle += 2 * M_PI;
    else if (ray->angle > 2 * M_PI) // wiht or witout else?
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
        
        draw_3d_wall_slice(d, x, distance, ray->angle, hit_vertical);
        // draw_3d_wall_slice(d, x, distance, ray->x, ray->y, ray->angle, hit_vertical);

        ray->angle += (60.0 * DEG_RAD) / WIN_WIDTH;
        
        if (ray->angle < 0)
            ray->angle += 2 * M_PI;
        if (ray->angle > 2 * M_PI)
            ray->angle -= 2 * M_PI;
    }
}

int render_frame(t_data *d)
{
    // Handle continuous movement every frame
    pl_control(d);
    
    // Clear screen to black
    for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
        ((uint32_t*)d->addr)[i] = 0x000000;
    
    t_ray ray;
    ray.angle = d->pl->angle;
    
    draw_3d_map(d, &ray);
    draw_minimap(d);
    mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
    return (0);
}