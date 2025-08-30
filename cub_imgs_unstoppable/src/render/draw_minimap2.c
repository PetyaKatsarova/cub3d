/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/06 16:56:33 by pekatsar          #+#    #+#             */
/*   Updated: 2025/08/15 19:46:16 by pekatsar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* make pl_x, pl_y center of the player 5px diameter dot */
void	draw_player_dot(t_data *d, int player_x,
			int player_y, t_minimap_params *params)
{
	int	x;
	int	y;

	y = -2;
	while (y <= 2)
	{
		x = -2;
		while (x <= 2)
		{
			if (player_x + x >= params->offset_x
				&& player_x + x < params->offset_x + MINIMAP_SIZE
				&& player_y + y >= params->offset_y
				&& player_y + y < params->offset_y + MINIMAP_SIZE)
				set_px(d, player_x + x, player_y + y, PL_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_player_direction(t_data *d, int player_x, int player_y)
{
	t_line_info	line;
	t_line_math	helper;

	line.x0 = player_x;
	line.y0 = player_y;
	line.x1 = player_x + (cos(d->pl->angle) * VECTOR_LEN);
	line.y1 = player_y + (sin(d->pl->angle) * VECTOR_LEN);
	line.color = PURPLE_RAY;
	draw_line(d, &line, &helper);
}

/*
** Creates a MINMAP_SIZE×MINMAP_SIZE max or d->map_rows and cols pixel rect.BACKGROUND_COL
** Positioned at top-right corner: offset_x, offset_y.
** Fills every pixel with BACKGROUND_COLOR (gray).
*/
void	draw_minimap_background(t_data *d, int offset_x, int offset_y,
			t_minimap_params *params)
{
	int	x;
	int	y;

	y = 0;
	while (y < d->map_rows * TILE_SIZE * params->scale)
	{
		x = 0;
		while (x < d->map_cols * TILE_SIZE * params->scale)
		{
			set_px(d, offset_x + x, offset_y + y, BACKGROUND_COLOR);
			x++;
		}
		y++;
	}
}
