/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/01 14:51:30 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/08/08 12:26:35 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * Connects two points with a straight line made of pxs
 * start at (0,0) and end at (4,2).
Compute total move:
dx = 4 − 0 = 4 px
dy = 2 − 0 = 2 px
Choose STEP_SIZEs: the larger of |4| and |2| is 4.
Compute per‐STEP_SIZE move:
x_inc = dx/STEP_SIZEs = 4/4 = 1 px
y_inc = dy/STEP_SIZEs = 2/4 = 0.5 px
Draw:
STEP_SIZE 0: plot at (0,0)
STEP_SIZE 1: move to (1,0.5) → plot at (1,0)
STEP_SIZE 2: move to (2,1.0) → plot at (2,1)
STEP_SIZE 3: move to (3,1.5) → plot at (3,1)
STEP_SIZE 4: move to (4,2.0) → plot at (4,2)
 */
void	draw_line(t_data *data, t_line_info *line_info)
{
	float	distance_x;
	float	distance_y;
	int		STEP_SIZEs;
	float	x_increment;
	float	y_increment;
	int		i;

	distance_x = line_info->x1 - line_info->x0;
	distance_y = line_info->y1 - line_info->y0;
	STEP_SIZEs = fabs(distance_y);
	if (fabs(distance_x) > fabs(distance_y))
		STEP_SIZEs = fabs(distance_x);
	x_increment = distance_x / STEP_SIZEs;
	y_increment = distance_y / STEP_SIZEs;
	i = 0;
	while (i < STEP_SIZEs)
	{
		if (line_info->x0 >= 0 && line_info->x0 < WIN_WIDTH && line_info->y0 >= 0 && line_info->y0 < WIN_HEIGHT)
			set_px(data, (int)line_info->x0, (int)line_info->y0, line_info->color);
		line_info->x0 += x_increment;
		line_info->y0 += y_increment;
		i++;
	}
}

/* keep it in the range [0, 2*PI] */
double normalize_angle(double angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle >= 2 * M_PI)
        angle -= 2 * M_PI;
    return angle;
}

/*
	Creates a MINMAP_SIZE×MINMAP_SIZE pixel rectangle
	Positioned at top-right corner: offset_x, offset_y
	Fills every pixel with BACKGROUND_COLOR (gray)
*/
void	draw_minimap_background(t_data *d, int offset_x, int offset_y)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			set_px(d, offset_x + x, offset_y + y, BACKGROUND_COLOR);
			x++;
		}
		y++;
	}
}

/*
loop through starty/endy startx/endx tile and fill each px with wall color
*/
static void	draw_wall_block(t_data *d, t_minimap_params *params)
{
	int	x;
	int	y;

	y = params->start_y;
	while (y < params->end_y && y < params->offset_y + MINIMAP_SIZE)
	{
		x = params->start_x;
		while (x < params->end_x && x < params->offset_x + MINIMAP_SIZE)
		{
			if (x >= params->offset_x && y >= params->offset_y)
				set_px(d, x, y, WALL_COLOR);
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
	while (map_y < ROWS)
	{
		map_x = 0;
		while (map_x < COLS)
		{
			if (d->map[map_y][map_x] == '1')
			{
				params.offset_x = offset_x;
				params.offset_y = offset_y;
				params.start_x = offset_x + (map_x * TILE_SIZE * scale);
				params.start_y = offset_y + (map_y * TILE_SIZE * scale);
				params.end_x = params.start_x + (int)ceil(TILE_SIZE * scale);
				params.end_y = params.start_y + (int)ceil(TILE_SIZE * scale);
				draw_wall_block(d, &params);
			}
			map_x++;
		}
		map_y++;
	}
}

