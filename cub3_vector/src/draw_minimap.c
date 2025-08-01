/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/01 14:51:30 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/01 16:54:43 by pekatsar      ########   odam.nl         */
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

// 2D minimap in corner
void draw_minimap(t_data *d)
{
    int minimap_size = 400; //350;  // 200x200 pixels
    int offset_x = WIN_WIDTH - minimap_size - 10;  // Top right corner
    int offset_y = 10;
    float scale = (float)minimap_size / (COLS * TILE_SIZE);  // Scale factor
    
    // Draw minimap background
    for (int y = 0; y < minimap_size; y++)
    {
        for (int x = 0; x < minimap_size; x++)
        {
            set_px(d, offset_x + x, offset_y + y, BACKGROUND_COLOR);  // Dark gray background
        }
    }
    
    // Draw map walls
    for (int map_y = 0; map_y < ROWS; map_y++)
    {
        for (int map_x = 0; map_x < COLS; map_x++)
        {
            if (d->map[map_y][map_x] == '1')
            {
                int start_x = offset_x + (map_x * TILE_SIZE * scale);
                int start_y = offset_y + (map_y * TILE_SIZE * scale);
                int end_x = start_x + (int)ceil(TILE_SIZE * scale);  // Use ceil instead of +1
           		int end_y = start_y + (int)ceil(TILE_SIZE * scale);
                
                // Draw wall block
                for (int y = start_y; y < end_y && y < offset_y + minimap_size; y++)
                {
                    for (int x = start_x; x < end_x && x < offset_x + minimap_size; x++)
                    {
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
    for (int y = -2; y <= 2; y++)
    {
        for (int x = -2; x <= 2; x++)
        {
            if (player_x + x >= offset_x && player_x + x < offset_x + minimap_size &&
                player_y + y >= offset_y && player_y + y < offset_y + minimap_size)
                set_px(d, player_x + x, player_y + y, LIME_YELLOW);
        }
    }
    
    // Draw player direction vector
    int dir_end_x = player_x + (cos(d->pl->angle) * 20);
    int dir_end_y = player_y + (sin(d->pl->angle) * 20);
    draw_line(d, player_x, player_y, dir_end_x, dir_end_y, PURPLE);  // Purple direction line
    
    // Draw some rays for visualization
    float ray_angle = d->pl->angle - (30.0 * DEG_RAD);
    for (int i = 0; i < RAYS_NUM; i++)  // Just 5 rays to avoid clutter
    {
        t_ray ray;
        ray.angle = ray_angle;
        
        float hx, hy, vx, vy;
        horizontal_check(&ray, d, &hx, &hy);
        vertical_check(&ray, d, &vx, &vy);
        
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
        if (ray_end_x >= offset_x && ray_end_x < offset_x + minimap_size &&
            ray_end_y >= offset_y && ray_end_y < offset_y + minimap_size)
            draw_line(d, player_x, player_y, ray_end_x, ray_end_y, pl_COLOR);  // Player color for rays
        
        ray_angle += (60.0 * DEG_RAD) / RAYS_NUM;  // Spread 5 rays across FOV
    }
}