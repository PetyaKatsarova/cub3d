/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vertical_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/15 20:01:15 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/23 17:53:24 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*
** Initialize vertical ray casting to the LEFT (west direction).
** Sets starting point at left edge of current tile.
When a ray touches the exact border between 2 tiles, computer can’t decide which wall to take → tiny holes.
Adding EPS = push the hit a hair inside the right tile → always picks the correct wall → no gaps.
*/
static void	init_v_ray_left(t_data *d, t_ray_params *p)
{
	p->vx = floor(d->pl->x / TILE_SIZE) * TILE_SIZE - (TILE_SIZE * EPS);
	p->vy = (d->pl->x - p->vx) * p->v_tan + d->pl->y;
	p->xo = -TILE_SIZE;
	p->yo = -p->xo * p->v_tan;
}

/*
** Initialize vertical ray casting to the RIGHT (east direction).
** Sets starting point at right edge of current tile.
*/
static void	init_v_ray_right(t_data *d, t_ray_params *p)
{
	p->vx = floor(d->pl->x / TILE_SIZE) * TILE_SIZE + TILE_SIZE + EPS;
	p->vy = (d->pl->x - p->vx) * p->v_tan + d->pl->y;
	p->xo = TILE_SIZE;
	p->yo = -p->xo * p->v_tan;
}

/*
** Cast vertical ray step by step until hitting a wall.
** Checks each vertical grid line intersection.
*/
static void	v_check_helper(t_data *d, t_ray_params *p)
{
	int	map_x;
	int	map_y;

	map_x = 0;
	map_y = 0;
	while (p->dof < (d->map_cols + d->map_rows) * 4)
	{
		map_x = (int)floor(p->vx / TILE_SIZE);
		map_y = (int)floor(p->vy / TILE_SIZE);
        if (map_x < 0 || map_x >= d->map_cols || map_y < 0 || map_y >= d->map_rows)
            break;
        if (d->map[map_y][map_x] == '1')
            break;
		p->vx += p->xo;
		p->vy += p->yo;
		p->dof++;
	}
}

/*
** Determines direction and initiates ray casting.
*/
void	vertical_check(t_ray *ray, t_data *d, t_ray_params *p)
{
	p->v_tan = -tan(ray->angle);
	p->dof = 0;
	if (ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2)
		init_v_ray_left(d, p);
	else if (ray->angle < M_PI / 2 || ray->angle > 3 * M_PI / 2)
		init_v_ray_right(d, p);
	else
	{
		p->vx = d->pl->x;
		p->vy = d->pl->y;
		p->dof = d->map_cols;
		return ;
	}
	v_check_helper(d, p);
}
