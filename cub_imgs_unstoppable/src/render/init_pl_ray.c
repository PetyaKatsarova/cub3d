/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_pl_ray.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/25 16:26:59 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/29 15:47:31 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	init_pl(t_pl *pl, t_game_configs *game_configs)
{
	char	dir;

	pl->x = game_configs->player_start_col * TILE_SIZE + (TILE_SIZE / 2);
	pl->y = game_configs->player_start_row * TILE_SIZE + (TILE_SIZE / 2);
	dir = game_configs->player_start_orientation;
	if (dir == 'N')
		pl->angle = 3 * M_PI / 2;
	else if (dir == 'S')
		pl->angle = M_PI / 2;
	else if (dir == 'E')
		pl->angle = 0;
	else if (dir == 'W')
		pl->angle = M_PI;
	else
		return (1);
	pl->delta_x = cos(pl->angle) * 5;
	pl->delta_y = sin(pl->angle) * 5;
	pl->fov = 60 * DEG_RAD;
	return (0);
}

void	init_ray_params(t_ray_params *params)
{
	params->h_tan = 0.0;
	params->v_tan = 0.0;
	params->dof = 0;
	params->x_offset = 0.0;
	params->y_offset = 0.0;
	params->hx = 0.0;
	params->hy = 0.0;
	params->vx = 0.0;
	params->vy = 0.0;
}
