/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/25 16:26:59 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/07/25 17:33:33 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int init_player (t_player *player, int x, int y, char dir)
{
	// todo: take from map
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
	{
		write(2, "Invalid player position\n", 24);
		return (1);
	}
	player->x = x * TILE_SIZE + TILE_SIZE / 2; // check logic : TODO
	player->y = y * TILE_SIZE + TILE_SIZE / 2;
	// TODO: take from parser
	/*
	player_angle showd dir the player is facing
		- N: 270 degrees; - S: 90 degrees (M_PI / 2); reversed for y axis for the screen
		- E: 0 degrees; W: 180 degrees (M_PI)
	*/
	if (dir == 'N')
		player->angle = 3 * M_PI / 2; // 
	else if (dir == 'S')
		player->angle = M_PI / 2;
	else if (dir == 'E')
		player->angle = 0;
	else if (dir == 'W')
		player->angle = M_PI;
	else
		return (1);
	player->delta_x = cos(player->angle);
	player->delta_y = sin(player->angle);
	return (0);
}
