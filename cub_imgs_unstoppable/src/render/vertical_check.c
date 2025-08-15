/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vertical_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/15 20:01:15 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/15 20:01:18 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	init_v_ray_left(t_data *d, t_ray_params *p)
{
	p->vx = floor(d->pl->x / TILE_SIZE) * TILE_SIZE - 0.0001;
	p->vy = (d->pl->x - p->vx) * p->v_tan + d->pl->y;
	p->xo = -TILE_SIZE;
	p->yo = -p->xo * p->v_tan;
}

static void	init_v_ray_right(t_data *d, t_ray_params *p)
{
	p->vx = floor(d->pl->x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	p->vy = (d->pl->x - p->vx) * p->v_tan + d->pl->y;
	p->xo = TILE_SIZE;
	p->yo = -p->xo * p->v_tan;
}

static void	v_check_helper(t_data *d, t_ray_params *p)
{
	int	map_x;
	int	map_y;

	map_x = 0;
	map_y = 0;
	while (p->dof < d->map_cols)
	{
		map_x = (int)floor(p->vx / TILE_SIZE);
		map_y = (int)floor(p->vy / TILE_SIZE);
		if (map_x >= 0 && map_x < d->map_cols && map_y >= 0
			&& map_y < d->map_rows && d->map[map_y][map_x] == '1')
			break ;
		p->vx += p->xo;
		p->vy += p->yo;
		p->dof++;
	}
}

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
