/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_pl.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/25 16:26:59 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/07/25 17:33:33 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int init_pl (t_pl *pl, t_game_configs *game_configs)
{
	pl->x = game_configs->player_start_col * TILE_SIZE;
	pl->y = game_configs->player_start_row * TILE_SIZE;
	char dir = game_configs->player_start_orientation;
	if ( dir== 'N') // cause screen is inverted, on paper is pi/2: 90 deg
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
