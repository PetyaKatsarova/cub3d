#include "../../include/cub3D.h"

static void setup_rayangle(t_data *d, t_ray *ray)
{
    ray->angle = d->pl->angle - (30.0 * DEG_RAD);
    if (ray->angle < 0)
        ray->angle += 2 * M_PI;
    else if (ray->angle > 2 * M_PI)
        ray->angle -= 2 * M_PI;
}

static void	draw_3d_map(t_data *d, t_ray *ray)
{
    t_ray_params	params;
    float			hdist, vdist;
    t_wall_info		wall;
    int				x;

    setup_rayangle(d, ray);
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
        // wall.raw_dist = wall.distance;
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
    if (d->focus == true)
        mlx_mouse_move(d->mlx, d->win, WIN_WIDTH / 2, WIN_HEIGHT / 2); 
    return (0);
}