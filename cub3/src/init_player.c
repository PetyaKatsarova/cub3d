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

#include "../include/cub3d.h"

int init_pl (t_pl *pl, int x, int y, char dir)
{
	// todo: take from map
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
	{
		write(2, "Invalid pl position\n", 24);
		return (1);
	}
	pl->x = x * TILE_SIZE + TILE_SIZE / 2; // check logic : TODO
	pl->y = y * TILE_SIZE + TILE_SIZE / 2;
	// TODO: take from parser
	/*
	pl_angle showd dir the pl is facing
		- N: 270 degrees; - S: 90 degrees (M_PI / 2); reversed for y axis for the screen
		- E: 0 degrees; W: 180 degrees (M_PI)
	*/
	if (dir == 'N')
		pl->angle = 3 * M_PI / 2; // 
	else if (dir == 'S')
		pl->angle = M_PI / 2;
	else if (dir == 'E')
		pl->angle = 0;
	else if (dir == 'W')
		pl->angle = M_PI;
	else
		return (1);
	pl->delta_x = cos(pl->angle);
	pl->delta_y = sin(pl->angle);
	return (0);
}
