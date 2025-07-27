#include "../include/cub3d.h"

int init_ray(t_ray *ray)
{
    ray->angle = 0;
    ray->distance = 0;
    ray->hit_vertical = 0;
    ray->y = 0;
    ray->x = 0;
}