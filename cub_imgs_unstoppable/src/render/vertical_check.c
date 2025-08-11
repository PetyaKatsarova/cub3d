#include "../../include/cub3D.h"

static void	init_v_ray_left(t_data *d, t_ray *ray, t_ray_params *params)
{
    /*
    When casting rays, if you land exactly on a grid line (e.g., x = 64.0), floating-point rounding can cause the ray to sometimes "see" the wrong tile (the one to the right instead of the one to the left).
    By subtracting a tiny value (0.0001), you make sure the ray is just inside the tile on the left, so your wall detection is accurate.
    (d->pl->x / TILE_SIZE) convert from px to tile index and back to px * tilesize
    */
    params->vx = floor(d->pl->x / TILE_SIZE) * TILE_SIZE - 0.0001;
    params->vy = (d->pl->x - params->vx) * params->v_tan + d->pl->y;
    params->xo = -TILE_SIZE;
    params->yo = -params->xo * params->v_tan;
}

static void	init_v_ray_right(t_data *d, t_ray *ray, t_ray_params *params)
{
    params->vx = floor(d->pl->x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
    params->vy = (d->pl->x - params->vx) * params->v_tan + d->pl->y;
    params->xo = TILE_SIZE;
    params->yo = -params->xo * params->v_tan;
}

static void	v_check_helper(t_data *d, t_ray_params *params)
{
    int	map_x;
    int	map_y;

    map_x = 0;
    map_y = 0;
    while (params->dof < d->map_cols)
    {
        map_x = (int)floor(params->vx / TILE_SIZE);
        map_y = (int)floor(params->vy / TILE_SIZE);
        if (map_x >= 0 && map_x < d->map_cols && map_y >= 0 
            && map_y < d->map_rows && d->map[map_y][map_x] == '1')
            break ;
        else
        {
            params->vx += params->xo;
            params->vy += params->yo;
            params->dof++;
        }
    }
}

void	vertical_check(t_ray *ray, t_data *d, t_ray_params *params)
{
    params->v_tan = -tan(ray->angle);
    params->dof = 0;
    if (ray->angle > M_PI/2 && ray->angle < 3*M_PI/2)
        init_v_ray_left(d, ray, params);
    else if (ray->angle < M_PI/2 || ray->angle > 3*M_PI/2)
        init_v_ray_right(d, ray, params);
    else
    {
        params->vx = d->pl->x;
        params->vy = d->pl->y;
        params->dof = d->map_cols;
        return ;
    }
    v_check_helper(d, params);
}
