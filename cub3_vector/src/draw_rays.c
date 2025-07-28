#include "../include/cub3d.h"

static void set_px(t_data *d, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		uint32_t *pixels = (uint32_t *)d->addr;
		int index = y * (d->line_length / 4) + x;
		pixels[index] = color;
	}
}

static void draw_line(t_data *data, float x0, float y0, float x1, float y1, uint32_t color)
{
    float dx = x1 - x0;
    float dy = y1 - y0;
    // absolute value of floating-point number = fabsf
    int steps = ( fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
    float x_inc = dx / steps;
    float y_inc = dy / steps;
//     float x = x0;
//     float y = y0;

    for (int i = 0; i < steps; i++)
    {
        if (x0 >= 0 && x0 < WIN_WIDTH && y0 >= 0 && y0 < WIN_HEIGHT)
            set_px(data, (int)x0, (int)y0, color);
        x0+= x_inc;
        y0+= y_inc;
    }
}

static void draw_rays (t_data *d, t_ray *ray) 
{
    // int r, mx, my, mp, dof;
    // float rx, ry, ra, xo, yo
    for (int r=0; r<1; r++)
    {
        // x checks
        float aTan = -1/tan(ray->angle);
        int dof = 0;
        float  move_x = 0, move_y = 0;
        if (ray->angle > M_PI) { // looking up
            // >>6 = /64 The >>6 followed by <<6 operations effectively round down the player's Y coordinate to the nearest multiple of 64 (
            ray->y = (((int)d->pl->y>>6)<<6)-0.0001;
            ray->x = (d->pl->y - ray->y) * aTan + d->pl->x;
            move_y = -TILE_SIZE;
            move_x = -move_y * aTan;
        }
        else if (ray->angle < M_PI) { // looking down
            ray->y = (((int)d->pl->y>>6)<<6)+TILE_SIZE;
            ray->x = (d->pl->y - ray->y) * aTan + d->pl->x;
            move_y = TILE_SIZE;
            move_x = -move_y * aTan;
        }
        else // looking straight left/right
        {
            ray->x = d->pl->x;
            ray->y = d->pl->y;
            dof = COLS;
        }
        while (dof < COLS)
        {
            int map_x = (int)(ray->x) / TILE_SIZE; // isnt this COLS
            int map_y = (int)(ray->y) / TILE_SIZE; // ROWS??
            // int mp = map_y*COLS + map_x;

            if (map_x >= 0 && map_x < COLS && map_y >= 0 && map_y < ROWS && d->map[map_y][map_x] == '1')
            {
                dof = COLS;
            }
            else {
                ray->x += move_x;
                ray->y += move_y;
                dof++;
            }

            // veritalc checks *** NB

        // float nTan = -tan(ray->angle);
        // dof = 0;
        // float  move_x = 0, move_y = 0;
        // if (ray->angle > P2 && ray->angle < P3) { // looking LEFT
        //     ray->x = (((int)d->pl->x>>6)<<6)-0.0001;
        //     ray->y = (d->pl->x - ray->x) * nTan + d->pl->y;
        //     move_x = -TILE_SIZE;
        //     move_y = -move_x * nTan;
        // }
        // else if (ray->angle < P2 || ray->angle > P3) { // looking RIGTH
        //     ray->x = (((int)d->pl->x>>6)<<6)+TILE_SIZE;
        //     ray->y = (d->pl->x - ray->x) * nTan + d->pl->y;
        //     move_x = TILE_SIZE;
        //     move_y = -move_x * nTan;
        // }
        // else if (ray->angle == 0 || ray->angle == PI) // looking straight up || down
        // {
        //     ray->x = d->pl->x;
        //     ray->y = d->pl->y;
        //     dof = COLS;
        // }
        // while (dof < COLS)
        // {
        //     int map_x = (int)(ray->x) / TILE_SIZE; // isnt this COLS
        //     int map_y = (int)(ray->y) / TILE_SIZE; // ROWS??
        //     // int mp = map_y*COLS + map_x;

        //     if (map_x >= 0 && map_x < COLS && map_y >= 0 && map_y < ROWS && d->map[map_y][map_x] == '1')
        //     {
        //         dof = COLS;
        //     }
        //     else {
        //         ray->x += move_x;
        //         ray->y += move_y;
        //         dof++;
        //     }
        // }
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

