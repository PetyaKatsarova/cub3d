/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/01 14:51:30 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/09/11 18:46:51 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* 

Bresenham’s algorithm
** Connects two points with a straight line made of pxs on a grid
** start at (0,0) and end at (4,2).
** Compute total move:
** dx = 4 − 0 = 4 px
** dy = 2 − 0 = 2 px
** Choose step_size: the larger of |4| and |2| is 4.
** Compute per-step_size move:
** x_inc = dx/step_size = 4/4 = 1 px
** y_inc = dy/step_size = 2/4 = 0.5 px
** Draw:
** step_size0: plot at (0,0)
** step_size1: move to (1,0.5) → plot at (1,0)
** step_size2: move to (2,1.0) → plot at (2,1)
** step_size3: move to (3,1.5) → plot at (3,1)
** step_size4: move to (4,2.0) → plot at (4,2)
calculates which pixels to color so the line looks as straight as possible,
using only integer math (no floating point).
distance_x, distance_y: total difference in x and y between start and end points.
x_incr, y_incr: how much to move in x and y for each step on the line.
*/
void	draw_line(t_data *data, t_line_info *line_info,
			t_line_math *line_math)
{
	int	step_size;
	int	i;

	line_math->distance_x = line_info->x1 - line_info->x0;
	line_math->distance_y = line_info->y1 - line_info->y0;
	step_size = fabs(line_math->distance_y);
	if (fabs(line_math->distance_x)
		> fabs(line_math->distance_y))
		step_size = fabs(line_math->distance_x);
	line_math->x_increment
		= line_math->distance_x / step_size;
	line_math->y_increment
		= line_math->distance_y / step_size;
	i = 0;
	while (i < step_size)
	{
		if (line_info->x0 >= 0 && line_info->x0 < WIN_WIDTH
			&& line_info->y0 >= 0 && line_info->y0 < WIN_HEIGHT)
			set_px(data, (int)line_info->x0, (int)line_info->y0,
				line_info->color);
		line_info->x0 += line_math->x_increment;
		line_info->y0 += line_math->y_increment;
		i++;
	}
}

/* keep it in the range [0, 2*PI] */
double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

/*
** loop through starty/endy startx/endx tile and fill each px with wall color
*/
static void	draw_wall_block(t_data *d, t_minimap_params *params, int offset_x,
	int offset_y)
{
	int	x;
	int	y;

	y = params->start_y;
	params->offset_x = offset_x;
	params->offset_y = offset_y;
	while (y < params->end_y)
	{
		x = params->start_x;
		while (x < params->end_x)
		{
			set_px(d, x, y, MINIMAP_WALL);
			x++;
		}
		y++;
	}
}

void	draw_minimap_walls(t_data *d, int offset_x, int offset_y, float scale)
{
	int					map_x;
	int					map_y;
	t_minimap_params	params;

	map_y = 0;
	while (map_y < d->map_rows)
	{
		map_x = 0;
		while (map_x < d->map_cols)
		{
			if (d->map[map_y][map_x] == '1')
			{
				params.start_x = offset_x + (map_x * TILE_SIZE * scale);
				params.start_y = offset_y + (map_y * TILE_SIZE * scale);
				params.end_x = params.start_x
					+ (int)ceil(TILE_SIZE * scale);
				params.end_y = params.start_y
					+ (int)ceil(TILE_SIZE * scale);
				draw_wall_block(d, &params, offset_x, offset_y);
			}
			map_x++;
		}
		map_y++;
	}
}
