#include "../include/cub3d.h"

void draw_rays (t_data *d, t_ray *ray) 
{
    // int r, mx, my, mp, dof;
    // float rx, ry, ra, xo, yo
    for (int r=0; r<1; r++)
    {
        d->pl->fov = 0;
        float aTan=-1/tan(ray->angle);
        if (ray->angle > M_PI) { // looking up
            ray->y = (((int)d->pl->y>>6)<<6)-0.0001;
            ray->x = (d->pl->y - ray->y) * aTan + d->pl->x;
            // whats o?
            // yo = -64;
            // xo = - yo*aTan;
        }
        if (ray->angle < M_PI) { // looking up
            ray->y = (((int)d->pl->y>>6)<<6)+TILE_SIZE;
            ray->x = (d->pl->y - ray->y) * aTan + d->pl->x;
            // yo = 64;
            // xo = - yo*aTan;
        }
        // while (dof < 8)
        // {
// video 8.42
        // }
    }
}