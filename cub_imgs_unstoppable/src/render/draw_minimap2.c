/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:56:33 by pekatsar          #+#    #+#             */
/*   Updated: 2025/08/11 18:23:58 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* make pl_x,pl_y center fo the player 5px dot diameter dot */
void	draw_player_dot(t_data *d, int player_x, int player_y, t_minimap_params *params)
{
	int	x;
	int	y;

	y = -2;
	while (y <= 2)
	{
		x = -2;
		while (x <= 2)
		{
			if (player_x + x >= params->offset_x && player_x + x < params->offset_x + MINIMAP_SIZE &&
				player_y + y >= params->offset_y && player_y + y < params->offset_y + MINIMAP_SIZE)
				set_px(d, player_x + x, player_y + y, LIME_YELLOW);
			x++;
		}
		y++;
	}
}

void	draw_player_direction(t_data *d, int player_x, int player_y)
{
	t_line_info	line;

	line.x0 = player_x;
	line.y0 = player_y;
	line.x1 = player_x + (cos(d->pl->angle) * VECTOR_LEN);
	line.y1 = player_y + (sin(d->pl->angle) * VECTOR_LEN);
	line.color = PURPLE_RAY;
	draw_line(d, &line);
}


