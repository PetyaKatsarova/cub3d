/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/01 14:51:30 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/02 15:17:19 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// Bresenham's line algorithm (for 2D debugging)
static void draw_line(t_data *data, float x0, float y0, float x1, float y1, uint32_t color)
{
    float distance_x = x1 - x0;
    float distance_y = y1 - y0;
    int steps = (fabs(distance_x) > fabs(distance_y)) ? fabs(distance_x) : fabs(distance_y);
    float x_increment = distance_x / steps;
    float y_increment = distance_y / steps;

    for (int i = 0; i < steps; i++)
    {
        if (x0 >= 0 && x0 < WIN_WIDTH && y0 >= 0 && y0 < WIN_HEIGHT)
            set_px(data, (int)x0, (int)y0, color);
        x0 += x_increment;
        y0 += y_increment;
    }
}

// Normalize angle to keep it in the range [0, 2*PI]
double normalize(double angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle >= 2 * M_PI)
        angle -= 2 * M_PI;
    return angle;
}

/*
void    draw_ray_2d(t_data *d, double angle, int color)
{
    double ray_x = d->pl_x;
    double ray_y = d->pl_y;
    double ray_dx = cos(angle);
    double ray_dy = sin(angle);
    int map_x = (int)ray_x;
    int map_y = (int)ray_y;

    while (map_x >= 0 && map_x < WIN_WIDTH / TILE_SIZE && map_y >= 0 && map_y < WIN_HEIGHT / TILE_SIZE)
    {
        if (d->map[map_y][map_x] == 1) // Wall hit
            break;
        ray_x += ray_dx;
        ray_y += ray_dy;
        map_x = (int)ray_x;
        map_y = (int)ray_y;
    }

    // Draw the ray on the 2D map (MLX function to plot a pixel)
    mlx_pixel_put(d->mlx, d->win, (int)ray_x, (int)ray_y, color);
}
*/

void draw_minimap(t_data *d)
{
    int offset_x = WIN_WIDTH - MINIMAP_SIZE - 10;  // Top right corner
    int offset_y = 10;
    float scale = (float)MINIMAP_SIZE / (COLS * TILE_SIZE);  // Scale factor
    
    // Draw minimap background
    for (int y = 0; y < MINIMAP_SIZE; y++) {
        for (int x = 0; x < MINIMAP_SIZE; x++) {
            set_px(d, offset_x + x, offset_y + y, BACKGROUND_COLOR);  // Dark gray background
        }
    }
    
    // Draw map walls
    for (int map_y = 0; map_y < ROWS; map_y++) {
        for (int map_x = 0; map_x < COLS; map_x++) {
            if (d->map[map_y][map_x] == '1') {
                int start_x = offset_x + (map_x * TILE_SIZE * scale);
                int start_y = offset_y + (map_y * TILE_SIZE * scale);
                int end_x = start_x + (int)ceil(TILE_SIZE * scale);  // Use ceil instead of +1
                int end_y = start_y + (int)ceil(TILE_SIZE * scale);
                
                // Draw wall block
                for (int y = start_y; y < end_y && y < offset_y + MINIMAP_SIZE; y++) {
                    for (int x = start_x; x < end_x && x < offset_x + MINIMAP_SIZE; x++) {
                        if (x >= offset_x && y >= offset_y)
                            set_px(d, x, y, WALL_COLOR);
                    }
                }
            }
        }
    }
    
    // Draw player position
    int player_x = offset_x + (d->pl->x * scale);
    int player_y = offset_y + (d->pl->y * scale);
    
    // Player dot (3x3 pixels)
    for (int y = -2; y <= 2; y++) {
        for (int x = -2; x <= 2; x++) {
            if (player_x + x >= offset_x && player_x + x < offset_x + MINIMAP_SIZE &&
                player_y + y >= offset_y && player_y + y < offset_y + MINIMAP_SIZE)
                set_px(d, player_x + x, player_y + y, LIME_YELLOW);
        }
    }
    
    // Draw player direction vector
    int dir_end_x = player_x + (cos(d->pl->angle) * 20);
    int dir_end_y = player_y + (sin(d->pl->angle) * 20);
    draw_line(d, player_x, player_y, dir_end_x, dir_end_y, PURPLE);  // direction line
    
    // Declare ray_angle here, starting at the left of the FOV and spreading rays across the FOV
    float ray_angle = normalize(d->pl->angle - (d->pl->fov / 2));  // Start rays at the center of FOV
    
    for (int i = 0; i < RAYS_NUM; i++) {
        t_ray ray;
        ray.angle = ray_angle;
        
        // Ray casting logic
        float hx, hy, vx, vy;
        horizontal_check(&ray, d, &hx, &hy);
        vertical_check(&ray, d, &vx, &vy);
        
        // Calculate the distance to the wall
        float hdist = sqrt((hx - d->pl->x) * (hx - d->pl->x) + (hy - d->pl->y) * (hy - d->pl->y));
        float vdist = sqrt((vx - d->pl->x) * (vx - d->pl->x) + (vy - d->pl->y) * (vy - d->pl->y));
        
        float hit_x, hit_y;
        if (hdist < vdist) {
            hit_x = hx;
            hit_y = hy;
        } else {
            hit_x = vx;
            hit_y = vy;
        }
        
        int ray_end_x = offset_x + (hit_x * scale);
        int ray_end_y = offset_y + (hit_y * scale);
        
        // Only draw if within minimap bounds
        if (ray_end_x >= offset_x && ray_end_x < offset_x + MINIMAP_SIZE &&
            ray_end_y >= offset_y && ray_end_y < offset_y + MINIMAP_SIZE)
            draw_line(d, player_x, player_y, ray_end_x, ray_end_y, PL_COLOR);  // Player color for rays
        
        // Evenly spread rays across the FOV
        ray_angle = normalize(ray_angle + (d->pl->fov / RAYS_NUM));
    }
}
