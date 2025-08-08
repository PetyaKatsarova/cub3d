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

#include "../include/cub3D.h"

int init_pl (t_pl *pl, int x, int y, char dir)
{
	// todo: take from map
	if (x < 0 || y < 0 || x >= (COLS * TILE_SIZE) || y >= (ROWS * TILE_SIZE))
	{
		write(2, "Invalid pl position\n", 24);
		return (1);
	}
	pl->x = x;
	pl->y = y;
	if (dir == 'N') // cause screen is inverted, on paper is pi/2: 90 deg
		pl->angle = 3 * M_PI / 2;
	else if (dir == 'S')
		pl->angle = M_PI / 2;
	else if (dir == 'E')
		pl->angle = 0;
	else if (dir == 'W')
		pl->angle = M_PI;
	else
		return (1);
	pl->delta_x = cos(pl->angle) * MOIVE_SPEED;
	pl->delta_y = sin(pl->angle) * MOIVE_SPEED;
	//pl.fov = 0; //field of view
	pl->fov = 60 * DEG_RAD;  // Set the FOV to 60 degrees
	return (0);
}



