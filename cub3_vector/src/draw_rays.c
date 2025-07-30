#include "../include/cub3d.h"

static void set_px(t_data *d, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		uint32_t *pixels = (uint32_t *)d->addr;
		/**
		 * line_length / 4 converts bytes to pixels
		 * d->addr is the address of the pixel data in the image
		 * Each pixel is 4 bytes (RGBA), so we divide by 4 to get the pixel index
		 * address is in bytes
		 */
		int index = y * (d->line_length / 4) + x;
		pixels[index] = color;
	}
}
/**
 * Bresenham's line algorithm (floating-point version) - draws a line between two points.
 */
static void draw_line(t_data *data, float x0, float y0, float x1, float y1, uint32_t color)
{
    float distance_x = x1 - x0; // haw far goind right
    float distance_y = y1 - y0; // how far going down
    // absolute value of floating-point number = fabsf 
	//Find longest axis (steps) - determines how many pixels to draw
    int steps = ( fabs(distance_x) > fabs(distance_y)) ? fabs(distance_x) : fabs(distance_y);
    float x_increment = distance_x / steps;
    float y_increment = distance_y / steps;
//     float x = x0;
//     float y = y0;

    for (int i = 0; i < steps; i++)
    {
        if (x0 >= 0 && x0 < WIN_WIDTH && y0 >= 0 && y0 < WIN_HEIGHT)
            set_px(data, (int)x0, (int)y0, color);
        x0+= x_increment;
        y0+= y_increment;
    }
}

static void draw_rays (t_data *d, t_ray *ray) 
{
    // int r, mx, my, mp, depth_of_field;
    // float rx, ry, ra, xo, yo
    for (int r=0; r<1; r++)
    {
        // Math helper for ray direction
        float aTan = -1/tan(ray->angle);
        int depth_of_field = 0; // just a counter not ot go out of bounds
        float  move_x = 0, move_y = 0;
        if (ray->angle > M_PI) { // looking up
            // round down the player's Y coordinate to the nearest multiple of 64 (
            ray->y = (((int)d->pl->y>>6)<<6)-0.0001; //// Start at grid line above player
            ray->x = (d->pl->y - ray->y) * aTan + d->pl->x;
            move_y = -TILE_SIZE;
            move_x = -move_y * aTan; // step sideways to match angle
        }
    	if (ray->angle < M_PI) { // looking down
            ray->y = (((int)d->pl->y>>6)<<6)+TILE_SIZE;
            ray->x = (d->pl->y - ray->y) * aTan + d->pl->x;
            move_y = TILE_SIZE;
            move_x = -move_y * aTan;
        }
        if (ray->angle == 0 || ray->angle == M_PI) // looking straight left/right
        {
            ray->x = d->pl->x;
            ray->y = d->pl->y;
            depth_of_field = COLS;
        }
        while (depth_of_field < COLS)
        {
            int map_x = (int)(ray->x) / TILE_SIZE; 
            int map_y = (int)(ray->y) / TILE_SIZE;

            if (map_x >= 0 && map_x < COLS && map_y >= 0 && map_y < ROWS && d->map[map_y][map_x] == '1')
            {
                depth_of_field = COLS;
            }
            else {
                ray->x += move_x;
                ray->y += move_y;
                depth_of_field++;
            }
        }

        draw_line(d, d->pl->x, d->pl->y, ray->x, ray->y, WALL_COLOR);
    }
}

int	render_frame(t_data *d)
{
	draw_maze(d);
	t_ray ray;
	ray.angle = d->pl->angle;
	draw_rays(d, &ray);
	draw_vector(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	return (0);
}


/**
 * render_frame(): Main drawing function called every frame
 * draw_rays(): Raycasting to find walls

float aTan = -1/tan(ray->angle);  // Math helper for ray direction
1. Pick starting point based on angle:
cif (ray->angle > M_PI) { // looking up
    ray->y = (((int)d->pl->y>>6)<<6)-0.0001;  // Start at grid line above player
    ray->x = (d->pl->y - ray->y) * aTan + d->pl->x;  // Calculate x position
    move_y = -TILE_SIZE;  // Step upward each time
    move_x = -move_y * aTan;  // Step sideways to match angle
}


 */
